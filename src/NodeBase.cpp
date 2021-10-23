#include "NodeBase.h"

namespace dpm
{
	NodeBase::NodeBase() = default;

	NodeBase::NodeBase(State &&state)
			: m_State(std::move(state))
	{
	}

	NodeBase::~NodeBase() = default;
}
