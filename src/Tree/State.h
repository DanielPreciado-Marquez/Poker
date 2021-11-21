#ifndef KUHN_POKER_STATE_H
#define KUHN_POKER_STATE_H

#include "Enums/PlayerAction.h"
#include "Hand.h"
#include "Outcome.h"
#include "PlayerMove.h"
#include "RuleSet/RuleSet.h"
#include "TurnOptions.h"
#include "Types/Cash.h"
#include "Types/PlayerIndex.h"
#include "Types/Turn.h"

namespace dpm
{
	template<GameMode TGameMode>
	struct State
	{
		using CommunityCards = std::array<Card, RuleSet<TGameMode>::NUMBER_OF_COMMUNITY_CARDS>;
		using PlayerHands = std::array<Hand<TGameMode>, RuleSet<TGameMode>::NUMBER_OF_PLAYERS>;
		using PreviousPlayerActions = std::array<PlayerAction, RuleSet<TGameMode>::NUMBER_OF_PLAYERS>;
		using Stakes = std::array<Cash, RuleSet<TGameMode>::NUMBER_OF_PLAYERS>;

	public:
		static State *createState(State &&state);

	public:
		CommunityCards communityCards;
		unsigned int currentRound;
		int numberOfRaises;
		PlayerHands playerHands;
		PlayerIndex previousPlayer;
		PreviousPlayerActions previousPlayerActions;
		Stakes stakes;
		Round round;

	public:
		State();

		State(Cash smallBlind, Cash bigBlind);

		explicit State(const PlayerHands &playerCards, Cash smallBlind, Cash bigBlind);

		State(const CommunityCards &communityCards, const PlayerHands &playerCards, PlayerIndex previousPlayer,
		      PreviousPlayerActions previousPlayerActions, const Stakes &stakes, Round round);

		State(const State &state) = default;

		~State() = default;

		[[nodiscard]]
		State copyState() const;

		[[nodiscard]]
		virtual bool isTerminal() const;

		[[nodiscard]]
		unsigned int getNumberOfCommunityCards() const;

		void applyMove(const Move &move, PlayerIndex playerIndex);

		State nextState(const Move &move, PlayerIndex playerIndex) const;

		[[nodiscard]]
		TurnOptions<TGameMode> getTurnOptions() const;

		[[nodiscard]]
		std::vector<Card> getAvailableCards() const;

		[[nodiscard]]
		Outcome getOutcome() const;

		[[nodiscard]]
		bool playerHandsEqual(const PlayerHands &otherPlayerHands) const;

	private:
		static std::vector<std::unique_ptr<State>> s_States;

	};

	template<GameMode TGameMode>
	std::vector<std::unique_ptr<State<TGameMode>>> State<TGameMode>::s_States = {};

	template<GameMode TGameMode>
	State<TGameMode> *State<TGameMode>::createState(State &&state)
	{
		s_States.push_back(std::make_unique<State<TGameMode>>(std::move(state)));
		return s_States.back().get();
	}

	template<GameMode TGameMode>
	State<TGameMode>::State()
			: communityCards()
			, currentRound(0)
			, numberOfRaises(0)
			, playerHands()
			, previousPlayer(PlayerIndices::NoPlayer)
			, previousPlayerActions()
			, stakes()
			, round(Rounds::NoRound)
	{
	}

	template<GameMode TGameMode>
	State<TGameMode>::State(const Cash smallBlind, const Cash bigBlind)
			: communityCards()
			, currentRound(0)
			, numberOfRaises(0)
			, playerHands()
			, previousPlayer(PlayerIndices::NoPlayer)
			, previousPlayerActions()
			, stakes()
			, round(Rounds::Round1)
	{
		for (auto &previousAction: previousPlayerActions)
			previousAction = PlayerAction::NoAction;

		stakes.at(0) = smallBlind;
		stakes.at(1) = bigBlind;
	}

	template<GameMode TGameMode>
	State<TGameMode>::State(const State::PlayerHands &playerCards, const Cash smallBlind, const Cash bigBlind)
			: communityCards()
			, currentRound(0)
			, numberOfRaises(0)
			, playerHands(playerCards)
			, previousPlayer(PlayerIndices::Dealer)
			, previousPlayerActions()
			, stakes()
			, round(Rounds::Round1)
	{
		for (auto &previousAction: previousPlayerActions)
			previousAction = PlayerAction::NoAction;

		stakes.at(0) = smallBlind;
		stakes.at(1) = bigBlind;
	}

	template<GameMode TGameMode>
	State<TGameMode>::State(const State::CommunityCards &communityCards, const State::PlayerHands &playerCards,
	                        const PlayerIndex previousPlayer, PreviousPlayerActions previousPlayerActions,
	                        const State::Stakes &stakes, const Round round)
			: communityCards(communityCards)
			, currentRound(0)
			, numberOfRaises(0)
			, playerHands(playerCards)
			, previousPlayer(previousPlayer)
			, previousPlayerActions(previousPlayerActions)
			, stakes(stakes)
			, round(round)
	{
	}

	template<GameMode TGameMode>
	State<TGameMode> State<TGameMode>::copyState() const
	{
		return State(*this);
	}

	template<GameMode TGameMode>
	bool State<TGameMode>::isTerminal() const
	{
		return true;
	}

	template<GameMode TGameMode>
	unsigned int State<TGameMode>::getNumberOfCommunityCards() const
	{
		for (auto i = 0u; i < communityCards.size(); ++i)
			if (communityCards.at(i).isEmpty())
				return i;
		return 0u;
	}

	template<GameMode TGameMode>
	void State<TGameMode>::applyMove(const Move &move, const PlayerIndex playerIndex)
	{
		if (move.getMoveType() == MoveType::DealerMove)
		{
			const auto &dealerMove = dynamic_cast<const DealerMove<TGameMode> &>(move);
			if (dealerMove.dealerAction == DealerAction::DrawPlayerCards)
				playerHands = dealerMove.hands;
			else if (dealerMove.dealerAction == DealerAction::DrawCommunityCards)
			{
				const auto numberCommunityCards = RuleSet<TGameMode>::NUMBER_OF_COMMUNITY_CARDS_PER_ROUND;
				const auto number = getNumberOfCommunityCards();
				communityCards.at(number) = dealerMove.communityCards.at(0);
				if (number + 1 >= numberCommunityCards.at(round))
					++round;
			}
		}
		else if (move.getMoveType() == MoveType::PlayerMove)
		{
			const auto &playerMove = dynamic_cast<const PlayerMove &>(move);
			previousPlayer = playerIndex;
			previousPlayerActions.at(playerIndex) = playerMove.playerAction;
			stakes.at(playerIndex) += playerMove.stake;
			if (playerMove.playerAction == PlayerAction::Raise)
				++numberOfRaises;
		}
	}

	template<GameMode TGameMode>
	State<TGameMode> State<TGameMode>::nextState(const Move &move, const PlayerIndex playerIndex) const
	{
		auto nextState = State(*this);
		nextState.applyMove(move, playerIndex);
		return std::move(nextState);
	}

	template<GameMode TGameMode>
	TurnOptions<TGameMode> State<TGameMode>::getTurnOptions() const
	{
		constexpr unsigned int numberOfPlayers = RuleSet<TGameMode>::NUMBER_OF_PLAYERS;
		bool allChecked = true;
		PlayerIndex lastBet = PlayerIndices::NoPlayer;
		PlayerIndex nextPlayerIndex = PlayerIndices::NoPlayer;

		for (auto i = 1u; i <= numberOfPlayers; ++i)
		{
			const auto indexToCheck = (previousPlayer + i) % numberOfPlayers;
			const auto playerAction = previousPlayerActions.at(indexToCheck);
			// check if no one bet or raised
			if (playerAction != PlayerAction::Check)
				allChecked = false;

			// check if all other players folded
			if (nextPlayerIndex == PlayerIndices::NoPlayer
			    && indexToCheck != previousPlayer
			    && playerAction != PlayerAction::Fold)
				nextPlayerIndex = indexToCheck;

			if (playerAction == PlayerAction::Bet)
				lastBet = indexToCheck;
		}

		if (lastBet == nextPlayerIndex)
			nextPlayerIndex = PlayerIndices::NoPlayer;

		// round ended
		if (allChecked || nextPlayerIndex == PlayerIndices::NoPlayer)
		{
			constexpr auto numberOfRounds = RuleSet<TGameMode>::NUMBER_OF_ROUNDS;
			if (round + 1 >= numberOfRounds)
				return TurnOptions<TGameMode>();

			const auto numberCommunityCards = RuleSet<TGameMode>::NUMBER_OF_COMMUNITY_CARDS_PER_ROUND;
			if (getNumberOfCommunityCards() < numberCommunityCards.at(round))
			{
				const auto availableCards = getAvailableCards();
				std::vector<DealerMove<TGameMode>> moves(availableCards.size());
				for (auto i = 0u; i < availableCards.size(); ++i)
					moves.at(i) = DealerMove<TGameMode>({availableCards.at(i)});
				return TurnOptions<TGameMode>(std::move(moves));
			}
			nextPlayerIndex = PlayerIndices::Player1;
			lastBet = PlayerIndices::NoPlayer;
		}

		// TODO stakes
		if (lastBet == PlayerIndices::NoPlayer && (round != 0 || RuleSet<TGameMode>::CAN_CHECK_IN_FIRST_ROUND))
		{
			// check, bet
			return TurnOptions<TGameMode>(nextPlayerIndex,
			                              {PlayerMove{PlayerAction::Check, 0},
			                               PlayerMove{PlayerAction::Bet, 1},
			                               PlayerMove{}});
		}
		else
		{
			// call, raise, fold
			if (numberOfRaises >= RuleSet<TGameMode>::NUMBER_OF_RAISES)
			{
				return TurnOptions<TGameMode>(nextPlayerIndex,
				                              {PlayerMove{PlayerAction::Call, 1},
				                               PlayerMove{},
				                               PlayerMove{PlayerAction::Fold, 0}});
			}
			else
			{
				return TurnOptions<TGameMode>(nextPlayerIndex,
				                              {PlayerMove{PlayerAction::Call, 1},
				                               PlayerMove{PlayerAction::Raise, 1},
				                               PlayerMove{PlayerAction::Fold, 0}});
			}
		}
	}

	template<GameMode TGameMode>
	std::vector<Card> State<TGameMode>::getAvailableCards() const
	{
		std::vector<Card> cards;
		for (const auto &card: RuleSet<TGameMode>::ALL_CARDS)
		{
			bool cardAvailable = true;
			for (const auto &communityCard: communityCards)
				if (card == communityCard)
					cardAvailable = false;
			if (!cardAvailable)
				continue;
			for (const auto &hand: playerHands)
				if (hand.containsCard(card))
					cardAvailable = false;
			if (cardAvailable)
				cards.emplace_back(card);
		}
		return std::move(cards);
	}

	template<GameMode TGameMode>
	Outcome State<TGameMode>::getOutcome() const
	{
		Cash pot = 0;
		for (const auto stake: stakes)
			pot += stake;

		PlayerIndex winner = PlayerIndices::NoPlayer;
		auto allButOneFolded = true;
		for (auto indexToCheck = 0u; indexToCheck < previousPlayerActions.size(); ++indexToCheck)
		{
			if (previousPlayerActions.at(indexToCheck) != PlayerAction::Fold)
			{
				if (winner == PlayerIndices::NoPlayer)
					winner = indexToCheck;
				else
					allButOneFolded = false;
			}
		}

		if (!allButOneFolded)
		{
			winner = 0;
			auto bestHand = playerHands.at(winner);
			for (auto indexToCheck = 1u; indexToCheck < playerHands.size(); ++indexToCheck)
			{
				const auto &handToCheck = playerHands.at(indexToCheck);
				if (bestHand < handToCheck)
				{
					winner = indexToCheck;
					bestHand = handToCheck;
				}
			}
		}

		return {winner, pot};
	}

	template<GameMode TGameMode>
	bool State<TGameMode>::playerHandsEqual(const State::PlayerHands &otherPlayerHands) const
	{
		for (auto i = 0u; i < playerHands.size(); ++i)
			if (playerHands.at(i) != otherPlayerHands.at(i))
				return false;
		return true;
	}

}

#endif //KUHN_POKER_STATE_H
