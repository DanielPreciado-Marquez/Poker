#ifndef KUHN_POKER_POKER_H
#define KUHN_POKER_POKER_H

#include "Enums/GameMode.h"
#include "Player.h"
#include "PlayerSlot.h "
#include "RuleSet/RuleSets.h"
#include "Tree/InitialGameState.hpp"
#include "Tree/RootNode.h"

namespace dpm
{

	template<GameMode TGameMode>
	class Poker
	{
	public:
		Poker();

		explicit Poker(RuleSet<TGameMode> &&ruleSet);

		void setPlayers(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players);

		float trainPlayer(unsigned int iterations, PlayerIndex playerIndex, bool playAgainstOtherPlayers);

	private:
		RuleSet<TGameMode> m_RuleSet;
		InitialGameState<TGameMode> m_GameState;

		std::array<PlayerSlot, RuleSet<TGameMode>::getNumberOfPlayers()> m_PlayerSlots;
		std::array<PlayerSlot *, RuleSet<TGameMode>::getNumberOfPlayers()> m_PlayerOrder;

		std::default_random_engine m_Rng;

	private:
		[[nodiscard]] typename State<TGameMode>::PlayerHands drawHands();

		void resetPlayerIndices();

		float cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
		          const State<TGameMode> *currentState,
		          PlayerIndex playerIndex,
		          History<TGameMode> &history,
		          std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
		          int playerIndexToUpdate) const;

	};

	template<GameMode TGameMode>
	Poker<TGameMode>::Poker()
			: Poker(RuleSet<TGameMode>())
	{
	}

	template<GameMode TGameMode>
	Poker<TGameMode>::Poker(RuleSet<TGameMode> &&ruleSet)
			: m_GameState({ruleSet.getSmallBlind(), ruleSet.getBigBlind()})
			, m_RuleSet(std::move(ruleSet))
			, m_PlayerSlots()
			, m_PlayerOrder()
	{
		m_GameState.generateChildren();
	}

	template<GameMode TGameMode>
	void Poker<TGameMode>::setPlayers(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players)
	{
		for (auto i = 0u; i < players.size(); ++i)
			m_PlayerSlots.at(i) = PlayerSlot{players.at(i)};
		dpm::Player playerA;
		resetPlayerIndices();
	}

	template<GameMode TGameMode>
	float Poker<TGameMode>::trainPlayer(const unsigned int iterations,
	                                    const PlayerIndex playerIndex,
	                                    const bool playAgainstOtherPlayers)
	{
		constexpr auto numberOfPlayers = RuleSet<TGameMode>::getNumberOfPlayers();
		std::array<Player *, numberOfPlayers> players;

		if (playAgainstOtherPlayers)
			for (auto i = 0u; i < numberOfPlayers; ++i)
				players.at(i) = m_PlayerSlots.at(i).player;
		else
			for (auto i = 0u; i < numberOfPlayers; ++i)
				players.at(i) = m_PlayerSlots.at(playerIndex).player;

		const auto playerIndexToUpdate = playAgainstOtherPlayers ? playerIndex : -1;

		auto regret = 0.0f;
		for (auto i = 0u; i < iterations; ++i)
		{
			auto hands = drawHands();
			History<TGameMode> history(std::move(hands));
			std::array<float, numberOfPlayers> reachProbabilities;
			for (auto &reachProbability: reachProbabilities)
				reachProbability = 1.0f;
			const auto gameState = m_GameState.getGameState(hands);
			regret += cfr(players,
			              gameState,
			              PlayerIndices::Player1,
			              history,
			              reachProbabilities,
			              playerIndexToUpdate);
			if (playAgainstOtherPlayers)
				std::rotate(players.begin(), players.begin() + 1, players.end());
		}
		const auto average = regret / float(iterations);
		return average;
	}

	template<GameMode TGameMode>
	typename State<TGameMode>::PlayerHands Poker<TGameMode>::drawHands()
	{
		constexpr auto numberOfPlayers = RuleSet<TGameMode>::NUMBER_OF_PLAYERS;
		constexpr auto numberOfCardsPerPlayer = RuleSet<TGameMode>::NUMBER_OF_CARDS_PER_PLAYER;

		auto deck = RuleSet<TGameMode>::getAllCards();
		std::shuffle(deck.begin(), deck.end(), m_Rng);
		typename State<TGameMode>::PlayerHands playerHands;
		for (auto playerIndex = 0u; playerIndex < numberOfPlayers; ++playerIndex)
			for (auto cardIndex = 0u; cardIndex < numberOfCardsPerPlayer; ++cardIndex)
				playerHands.at(playerIndex).addCard(deck.at(playerIndex * numberOfCardsPerPlayer + cardIndex));
		return playerHands;
	}

	template<GameMode TGameMode>
	void Poker<TGameMode>::resetPlayerIndices()
	{
		for (auto i = 0u; i < m_PlayerSlots.size(); ++i)
			m_PlayerOrder.at(i) = &m_PlayerSlots.at(i);
	}

	template<GameMode TGameMode>
	float Poker<TGameMode>::cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
	                            const State<TGameMode> *const currentState,
	                            const PlayerIndex playerIndex,
	                            History<TGameMode> &history,
	                            std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
	                            int playerIndexToUpdate) const
	{
		if (currentState->isTerminal())
		{
			// TODO more than 2 players
			const auto outcome = currentState->getOutcome();
			const auto playerStake = currentState->stakes.at(playerIndex);
			if (outcome.winner == playerIndex)
				return float(outcome.stake - playerStake);
			else
				return -float(playerStake);
		}
		// TODO Dealer
		auto currentGameState = dynamic_cast<const GameState<TGameMode> *const>(currentState);
		const auto possiblePlayerActions = currentGameState->getPlayerActions();
		const auto &playerHand = currentGameState->playerHands.at(playerIndex);
		auto &informationSet = players.at(playerIndex)->getInformationSet<TGameMode>(playerIndex,
		                                                                             history,
		                                                                             possiblePlayerActions);
		const auto strategy = informationSet.updateStrategy(reachProbabilities.at(playerIndex));

		std::array<float, NUMBER_OF_PLAYER_ACTIONS> counterfactualValues = {};
		auto counterfactualSum = 0.0f;

		// TODO more than 2 players
		const auto nextPlayerIndex = (playerIndex + 1) % 2;

		for (auto i = 0u; i < NUMBER_OF_PLAYER_ACTIONS; ++i)
		{
			const auto &childInfo = currentGameState->getChildren().at(i);
			const auto &playerMove = childInfo.playerMove;
			if (playerMove.playerAction == PlayerAction::NoAction)
				continue;
			const auto currentRoundIndex = history.getCurrentRoundIndex();
			const auto nextMoveIndex = history.getNextMoveIndex();
			history.applyMove(playerMove, playerIndex);
			auto nextReachProbabilities = reachProbabilities;
			nextReachProbabilities.at(playerIndex) *= strategy.at(i);
			const float counterfactualValue = -cfr(players,
			                                       childInfo.state,
			                                       nextPlayerIndex,
			                                       history,
			                                       nextReachProbabilities,
			                                       playerIndexToUpdate);
			counterfactualSum += strategy.at(i) * counterfactualValue;
			counterfactualValues.at(i) = counterfactualValue;
			history.rollback(currentRoundIndex, nextMoveIndex);
		}
		if (playerIndexToUpdate == -1 || playerIndexToUpdate == playerIndex)
		{
			for (auto i = 0u; i < NUMBER_OF_PLAYER_ACTIONS; ++i)
			{
				const auto &playerMove = currentGameState->getChildren().at(i).playerMove;
				if (playerMove.playerAction == PlayerAction::NoAction)
					continue;
				informationSet.updateCumulativeRegret(i,
				                                      reachProbabilities.at(nextPlayerIndex) *
				                                      (counterfactualValues.at(i) - counterfactualSum));
			}
		}
		return counterfactualSum;
	}

}

#endif //KUHN_POKER_POKER_H
