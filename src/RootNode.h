#ifndef KUHN_POKER_ROOTNODE_H
#define KUHN_POKER_OLD_ROOTNODE_H

#include "InternalNode.h"

namespace dpm::old
{
	class RootNode
	{
	public:
		RootNode();

		[[nodiscard]] Outcome getOutcome(const Hands &hands, const History &history) const;

		float trainPlayer(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
		                  PlayerIndex playerIndex,
		                  const Hands &hands,
		                  const History &history,
		                  ReachProbabilities reachProbabilities,
		                  int playerIndexToUpdate) const;

	private:
		// TODO Unused indices for same cards
		std::array<std::array<std::shared_ptr<InternalNode>, Cards::getNumberOfCards()>, Cards::getNumberOfCards()> m_Trees;

	private:
		void generateTrees();

		[[nodiscard]] InternalNode *getTreeFromHands(const Hands &hands) const;
	};
}

#endif //KUHN_POKER_ROOTNODE_H
