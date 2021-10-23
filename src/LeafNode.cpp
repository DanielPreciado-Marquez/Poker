#include "LeafNode.h"

namespace dpm
{
	LeafNode::LeafNode(State &&state)
			: NodeBase(std::move(state))
	{
	}

	Outcome LeafNode::getOutcome(const History &history) const
	{
		PlayerIndex winner;
		if (history.at(0) == Moves::Bet && history.at(1) == Moves::Fold)
			winner = PlayerIndices::Player1;
		else if (history.at(0) == Moves::Check && history.at(1) == Moves::Bet && history.at(2) == Moves::Fold)
			winner = PlayerIndices::Player2;
		else
			winner = m_State.cards.at(PlayerIndices::Player1) > m_State.cards.at(PlayerIndices::Player2)
			         ? PlayerIndices::Player1
			         : PlayerIndices::Player2;

		const auto stake = static_cast<Stake>(m_State.stakes.at(PlayerIndices::Player1) +
		                                      m_State.stakes.at(PlayerIndices::Player2));
		return {winner, stake};
	}

	float LeafNode::cfr(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
	                    const PlayerIndex playerIndex,
	                    const Hands &hands,
	                    const History &history,
	                    const ReachProbabilities reachProbabilities,
	                    const int playerIndexToUpdate) const
	{
		const auto outcome = getOutcome(history);
		if (outcome.winner == playerIndex)
			return float(outcome.stake - m_State.stakes.at(playerIndex));
		else
			return float(-m_State.stakes.at(playerIndex));

	}
}
