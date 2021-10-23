#ifndef KUHN_POKER_ROOTNODE_H
#define KUHN_POKER_ROOTNODE_H

#include "InternalNode.h"

namespace dpm
{
	class RootNode
	{
	public:
		RootNode();

		[[nodiscard]] Outcome getOutcome(const Hands &hands, const History &history) const;

		// TODO
		void train() const;

	private:
		// TODO Unused indices for same cards
		std::array<std::array<std::shared_ptr<InternalNode>, Cards::getNumberOfCards()>, Cards::getNumberOfCards()> m_Trees;

	private:
		void generateTrees();

		[[nodiscard]] InternalNode *getTreeFromHands(const Hands &hands) const;
	};
}

#endif //KUHN_POKER_ROOTNODE_H
