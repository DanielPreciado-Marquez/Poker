#include "LeafNode.h"

namespace dpm
{
	LeafNode::LeafNode(State &&state)
			: NodeBase(std::move(state))
	{
	}

	Outcome LeafNode::getOutcome(const History &history) const
	{
		PlayerIndex winner = m_State.cards.at(PlayerIndices::Player1) > m_State.cards.at(PlayerIndices::Player2)
		                     ? PlayerIndices::Player1
		                     : PlayerIndices::Player2;

		const auto stake = static_cast<Stake>(m_State.stakes.at(PlayerIndices::Player1) +
		                                      m_State.stakes.at(PlayerIndices::Player2));
		return {winner, stake};
	}
}
