#ifndef KUHN_POKER_INTERNALNODE_H_
#define KUHN_POKER_INTERNALNODE_H_

#include "Tree/NodeBase.h"

namespace dpm::old
{
	class InternalNode : public NodeBase
	{
	public:
		explicit InternalNode(State &&state);

		[[nodiscard]] Outcome getOutcome(const History &history) const override;

		[[nodiscard]] float cfr(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
		                        PlayerIndex playerIndex,
		                        const Hands &hands,
		                        const History &history,
		                        ReachProbabilities reachProbabilities,
		                        int playerIndexToUpdate) const override;

		[[nodiscard]] float cfr2(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
		                        PlayerIndex playerIndex,
		                        const Hands &hands,
		                        const History &history,
		                        ReachProbabilities reachProbabilities,
		                        int playerIndexToUpdate) const;

	private:
		std::array<std::shared_ptr<NodeBase>, Moves::getNumberOfMoves()> m_Children;

	private:
		void generateChildren();
	};
}

#endif //KUHN_POKER_INTERNALNODE_H
