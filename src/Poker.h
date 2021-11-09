#ifndef KUHN_POKER_POKER_H
#define KUHN_POKER_POKER_H

#include "Enums/GameMode.h"
#include "Player.h"
#include "PlayerSlot.h "
#include "RuleSet/RuleSets.h"
#include "Tree/RootNode.h"

namespace dpm
{

	template<GameMode TGameMode>
	class Poker
	{
	protected:
		using Hands = std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()>;

	public:
		Poker();

		explicit Poker(RuleSet<TGameMode> &&ruleSet);

		void setPlayers(const std::array<Player *, RuleSet<TGameMode>::getNumberOfPlayers()> &players);

		float trainPlayer(unsigned int iterations, PlayerIndex playerIndex, bool playAgainstOtherPlayers);

	private:
		RootNode<TGameMode> m_GameTree;
		RuleSet<TGameMode> m_RuleSet;

		std::array<PlayerSlot, RuleSet<TGameMode>::getNumberOfPlayers()> m_PlayerSlots;
		std::array<PlayerSlot *, RuleSet<TGameMode>::getNumberOfPlayers()> m_PlayerOrder;

		std::default_random_engine m_Rng;

	private:
		[[nodiscard]] Hands drawHands();

		void resetPlayerIndices();

	};

	template<GameMode TGameMode>
	Poker<TGameMode>::Poker()
			: Poker(RuleSet<TGameMode>())
	{
	}

	template<GameMode TGameMode>
	Poker<TGameMode>::Poker(RuleSet<TGameMode> &&ruleSet)
			: m_GameTree()
			, m_RuleSet(std::move(ruleSet))
			, m_PlayerSlots()
			, m_PlayerOrder()
	{
		m_GameTree.generateChildren(&m_RuleSet);
	}

	template<GameMode TGameMode>
	void Poker<TGameMode>::setPlayers(const std::array<Player *, RuleSet<TGameMode>::getNumberOfPlayers()> &players)
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
			History<TGameMode> history(std::move(hands), m_RuleSet.getSmallBlind(), m_RuleSet.getBigBlind());
			std::array<float, numberOfPlayers> reachProbabilities;
			for (auto &reachProbability: reachProbabilities)
				reachProbability = 1.0f;
			regret += m_GameTree.cfr(players,
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
	typename Poker<TGameMode>::Hands Poker<TGameMode>::drawHands()
	{
		constexpr auto numberOfPlayers = RuleSet<TGameMode>::getNumberOfPlayers();
		constexpr auto numberOfCardsPerPlayer = RuleSet<TGameMode>::getNumberOfCardsPerPlayer();

		auto deck = RuleSet<TGameMode>::getAllCards();
		std::shuffle(deck.begin(), deck.end(), m_Rng);
		Hands hands;
		for (auto playerIndex = 0u; playerIndex < numberOfPlayers; ++playerIndex)
			for (auto cardIndex = 0u; cardIndex < numberOfCardsPerPlayer; ++cardIndex)
				hands.at(playerIndex).addCard(deck.at(playerIndex * numberOfCardsPerPlayer + cardIndex));
		return hands;
	}

	template<GameMode TGameMode>
	void Poker<TGameMode>::resetPlayerIndices()
	{
		for (auto i = 0u; i < m_PlayerSlots.size(); ++i)
			m_PlayerOrder.at(i) = &m_PlayerSlots.at(i);
	}
}

#endif //KUHN_POKER_POKER_H
