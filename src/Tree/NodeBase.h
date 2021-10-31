#ifndef KUHN_POKER_NODEBASE_H
#define KUHN_POKER_NODEBASE_H

#include "Enums/GameMode.h"
#include "History.h"
#include "Outcome.h"
#include "State.h"

namespace dpm
{
	class Player;

	template<GameMode TGameMode>
	class NodeBase
	{
		using ReachProbabilities = std::array<float, RuleSet<TGameMode>::getNumberOfPlayers()>;

	public:
		NodeBase();

		explicit NodeBase(State<TGameMode> &&state);

		virtual ~NodeBase();

		virtual void generateChildren(const TurnOptions<TGameMode> &turnOptions, History<TGameMode> &history) = 0;

	protected:
		State<TGameMode> m_State;

	};

	template<GameMode TGameMode>
	NodeBase<TGameMode>::NodeBase() = default;

	template<GameMode TGameMode>
	NodeBase<TGameMode>::NodeBase(State<TGameMode> &&state)
			: m_State(std::move(state))
	{
	}

	template<GameMode TGameMode>
	NodeBase<TGameMode>::~NodeBase() = default;

}

#endif //KUHN_POKER_NODEBASE_H
