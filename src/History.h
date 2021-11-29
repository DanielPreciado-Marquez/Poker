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
	public:
		explicit History(typename State<TGameMode>::PlayerHands &&playerHands);

		[[nodiscard]] int getCurrentRoundIndex() const;

		[[nodiscard]] int getNextMoveIndex() const;

		void applyMove(const Move &move, PlayerIndex playerIndex);

		void beginNewRound();

		void rollback(unsigned int roundIndex, unsigned int moveIndex);

		[[nodiscard]] std::string toString(PlayerIndex playerIndex) const;

	private:
		std::vector<RoundHistory<TGameMode>> m_RoundHistories;
		unsigned int m_CurrentRound;
		unsigned int m_NextMove;

	};

	template<GameMode TGameMode>
	History<TGameMode>::History(typename State<TGameMode>::PlayerHands &&playerHands)
			: m_RoundHistories()
			, m_CurrentRound(0)
			, m_NextMove(0)
	{
		m_RoundHistories.emplace_back(DealerMove<TGameMode>(std::move(playerHands)));
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

	template<GameMode TGameMode>
	void History<TGameMode>::applyMove(const Move &move, const PlayerIndex playerIndex)
	{
		if (move.getMoveType() == MoveType::DealerMove)
		{
			const auto &dealerMove = dynamic_cast<const DealerMove<TGameMode> &>(move);
			if (dealerMove.dealerAction == DealerAction::DrawPlayerCards ||
			    dealerMove.dealerAction == DealerAction::DrawCommunityCards)
				m_RoundHistories.at(m_CurrentRound).addDealerMove(dealerMove);
		}
		else if (move.getMoveType() == MoveType::PlayerMove)
		{
			const auto &playerMove = dynamic_cast<const PlayerMove &>(move);
			m_RoundHistories.at(m_CurrentRound).addPlayerMove(playerMove, m_NextMove);
			++m_NextMove;
		}
	}

	template<GameMode TGameMode>
	void History<TGameMode>::beginNewRound()
	{
		m_RoundHistories.push_back({});
		m_CurrentRound += 1;
		m_NextMove = 0;
	}

	template<GameMode TGameMode>
	void History<TGameMode>::rollback(const unsigned int roundIndex, const unsigned int moveIndex)
	{
		m_CurrentRound = roundIndex;
		m_NextMove = moveIndex;
	}

	template<GameMode TGameMode>
	std::string History<TGameMode>::toString(const PlayerIndex playerIndex) const
	{
		std::stringstream ss;
		for (auto i = 0u; i < m_CurrentRound; ++i)
			ss << m_RoundHistories.at(i).toString(playerIndex);
		ss << m_RoundHistories.at(m_CurrentRound).toString(playerIndex, m_NextMove);
		return ss.str();
	}
}

#endif //KUHN_POKER_HISTORY_H
