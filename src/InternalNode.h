#ifndef KUHN_POKER_INTERNALNODE_H
#define KUHN_POKER_INTERNALNODE_H

#include "NodeBase.h"

namespace dpm
{
	class InternalNode : public NodeBase
	{
	public:
		explicit InternalNode(State &&state);

		[[nodiscard]] Outcome getOutcome(const History &history) const override;

	private:
		std::array<std::shared_ptr<NodeBase>, Moves::getNumberOfMoves()> m_Children;

	private:
		void generateChildren();
	};
}

#endif //KUHN_POKER_INTERNALNODE_H
