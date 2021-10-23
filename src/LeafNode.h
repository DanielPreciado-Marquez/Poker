#ifndef KUHN_POKER_LEAFNODE_H
#define KUHN_POKER_LEAFNODE_H

#include "NodeBase.h"

namespace dpm
{
	class LeafNode : public NodeBase
	{
	public:
		LeafNode(State &&state);

		Outcome getOutcome(const History &history) const override;

	private:
		PlayerIndex m_Winner;

	};
}

#endif //KUHN_POKER_LEAFNODE_H
