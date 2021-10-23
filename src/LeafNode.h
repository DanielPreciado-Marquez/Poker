#ifndef KUHN_POKER_LEAFNODE_H
#define KUHN_POKER_LEAFNODE_H

#include "NodeBase.h"

namespace dpm
{
	class LeafNode : public NodeBase
	{
	public:
		explicit LeafNode(State &&state);

		[[nodiscard]] Outcome getOutcome(const History &history) const override;

		[[nodiscard]] float cfr(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
		                        PlayerIndex playerIndex,
		                        const Hands &hands,
		                        const History &history,
		                        ReachProbabilities reachProbabilities,
		                        int playerIndexToUpdate) const override;

	};
}

#endif //KUHN_POKER_LEAFNODE_H
