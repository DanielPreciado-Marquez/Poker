#ifndef KUHN_POKER_NODEBASE_H
#define KUHN_POKER_NODEBASE_H

#include "Outcome.h"
#include "State.h"


namespace dpm
{
	class NodeBase
	{
	public:
		NodeBase();

		explicit NodeBase(State &&state);

		virtual ~NodeBase();

		[[nodiscard]] virtual Outcome getOutcome(const History &history) const = 0;

	protected:
		State m_State;
	};
}

#endif //KUHN_POKER_NODEBASE_H
