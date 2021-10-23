#include "NodeBase.h"

namespace dpm
{
	NodeBase::NodeBase() = default;

	NodeBase::NodeBase(State &&state)
			: m_State(std::move(state))
	{
	}

	NodeBase::~NodeBase() = default;

	unsigned int NodeBase::getHistoryIndex() const
	{
		return PlayerIndices::getNumberOfPlayers() * m_State.turn + m_State.nextPlayer;
	}
}
