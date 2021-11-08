#ifndef KUHN_POKER_HISTORY_H
#define KUHN_POKER_HISTORY_H

#include "DealerMove.h"
#include "PlayerMove.h"
#include "RoundHistory.h"
#include "Tree/State.h"
#include "TurnOptions.h"

namespace dpm
{

	template<GameMode TGameMode>
	class History
	{
	protected:
		using RoundHistory = RoundHistory<TGameMode>;
		using RuleSet = RuleSet<TGameMode>;
		using PlayerCards = std::array<Hand<TGameMode>, RuleSet::getNumberOfPlayers()>;
		using State = State<TGameMode>;
		using TurnOptions = TurnOptions<TGameMode>;

	public:
		explicit History(PlayerCards &&playerCards, Cash smallBlind, Cash bigBlind);

		[[nodiscard]] const State &getFinalState() const;

		[[nodiscard]] int getCurrentRoundIndex() const;

		[[nodiscard]] int getNextMoveIndex() const;

		void applyMove(const Move &move, PlayerIndex playerIndex);

		void rollback(const State &state, unsigned int roundIndex, unsigned int moveIndex);

		[[nodiscard]] TurnOptions getPossibleMoves() const;

	private:
		std::vector<RoundHistory> m_RoundHistories;
		State m_FinalState;

		unsigned int m_CurrentRound;
		unsigned int m_NextMove;

	};

	template<GameMode TGameMode>
	History<TGameMode>::History(PlayerCards &&playerCards, const Cash smallBlind, const Cash bigBlind)
			: m_RoundHistories()
			, m_FinalState(playerCards, smallBlind, bigBlind)
			, m_CurrentRound(0)
			, m_NextMove(0)
	{
		m_RoundHistories.emplace_back(DealerMove<TGameMode>(std::move(playerCards)));
	}

	template<GameMode TGameMode>
	const State<TGameMode> &History<TGameMode>::getFinalState() const
	{
		return m_FinalState;
	}

	template<GameMode TGameMode>
	void History<TGameMode>::applyMove(const Move &move, const PlayerIndex playerIndex)
	{
		if (move.getMoveType() == MoveType::DealerMove)
		{
			const auto &dealerMove = dynamic_cast<const DealerMove<TGameMode> &>(move);
			if (dealerMove.dealerAction == DealerAction::DrawPlayerCards)
			{
				m_FinalState.playerCards = dealerMove.hands;
				m_RoundHistories.emplace_back(DealerMove<TGameMode>(std::move(dealerMove.hands)));
			}
			else if (dealerMove.dealerAction == DealerAction::DrawCommunityCards)
			{
				// TODO
			}
		}
		else if (move.getMoveType() == MoveType::PlayerMove)
		{
			const auto &playerMove = dynamic_cast<const PlayerMove &>(move);
			m_FinalState.previousPlayer = playerIndex;
			m_FinalState.previousPlayerActions.at(playerIndex) = playerMove.playerAction;
			m_FinalState.stakes.at(playerIndex) += playerMove.stake;
			if (playerMove.playerAction == PlayerAction::Raise)
				++m_FinalState.numberOfRaises;
			m_RoundHistories.at(m_CurrentRound).addPlayerMove(playerMove, m_NextMove);
			++m_NextMove;
		}
	}

	template<GameMode TGameMode>
	void History<TGameMode>::rollback(const State &state, const unsigned int roundIndex, const unsigned int moveIndex)
	{
		m_FinalState = state;
		m_CurrentRound = roundIndex;
		m_NextMove = moveIndex;
	}

	template<GameMode TGameMode>
	TurnOptions<TGameMode> History<TGameMode>::getPossibleMoves() const
	{
		constexpr unsigned int numberOfPlayers = RuleSet::getNumberOfPlayers();
		bool allChecked = true;
		PlayerIndex lastBet = PlayerIndices::NoPlayer;
		PlayerIndex nextPlayerIndex = PlayerIndices::NoPlayer;

		for (auto i = 1u; i <= numberOfPlayers; ++i)
		{
			const auto indexToCheck = (m_FinalState.previousPlayer + i) % numberOfPlayers;
			const auto playerAction = m_FinalState.previousPlayerActions.at(indexToCheck);
			// check if no one bet or raised
			if (playerAction != PlayerAction::Check)
				allChecked = false;

			// check if all other players folded
			if (nextPlayerIndex == PlayerIndices::NoPlayer
			    && indexToCheck != m_FinalState.previousPlayer
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
			constexpr auto numberOfRounds = RuleSet::getNumberOfRounds();
			if (m_CurrentRound + 1 >= numberOfRounds)
				return TurnOptions();
			else
			{
				// TODO Dealer Move
				return TurnOptions();
			}
		}

		// TODO stakes
		if (lastBet == PlayerIndices::NoPlayer && (m_CurrentRound != 0 || RuleSet::canCheckInFirstRound()))
		{
			// check, bet
			return TurnOptions(nextPlayerIndex,
			                   {PlayerMove{PlayerAction::Check, 0},
			                    PlayerMove{PlayerAction::Bet, 1},
			                    PlayerMove{}});
		}
		else
		{
			// call, raise, fold
			if (m_FinalState.numberOfRaises >= RuleSet::getNumberOfRaises())
			{
				return TurnOptions(nextPlayerIndex,
				                   {PlayerMove{PlayerAction::Call, 1},
				                    PlayerMove{PlayerAction::Fold, 0},
				                    PlayerMove{}});
			}
			else
			{
				return TurnOptions(nextPlayerIndex,
				                   {PlayerMove{PlayerAction::Call, 1},
				                    PlayerMove{PlayerAction::Raise, 1},
				                    PlayerMove{PlayerAction::Fold, 0}});
			}
		}
	}

	template<GameMode TGameMode>
	int History<TGameMode>::getCurrentRoundIndex() const
	{
		return m_CurrentRound;
	}

	template<GameMode TGameMode>
	int History<TGameMode>::getNextMoveIndex() const
	{
		return m_NextMove;
	}
}

#endif //KUHN_POKER_HISTORY_H
