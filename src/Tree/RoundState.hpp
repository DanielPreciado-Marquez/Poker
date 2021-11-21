#ifndef POKER_ROUNDSTATE_HPP
#define POKER_ROUNDSTATE_HPP

#include "Tree/ChildInfo.hpp"
#include "Tree/State.h"

namespace dpm
{
	template<GameMode TGameMode>
	class RoundState : public State<TGameMode>
	{
	public:
		static RoundState *createRoundState(State<TGameMode> &&state);

	public:
		RoundState();

		RoundState(const RoundState &gameState) = default;

		explicit RoundState(State<TGameMode> &&state);

		[[nodiscard]]
		bool isTerminal() const override;

		void generateChildren(const TurnOptions<TGameMode> &turnOptions);

	private:
		static std::vector<std::unique_ptr<RoundState<TGameMode>>> s_RoundStates;

	private:
		std::array<ChildInfo<TGameMode>, RuleSet<TGameMode>::NUMBER_OF_POSSIBLE_COMMUNITY_CARDS> m_Children;

	};

	template<GameMode TGameMode>
	std::vector<std::unique_ptr<RoundState<TGameMode>>> RoundState<TGameMode>::s_RoundStates = {};

	template<GameMode TGameMode>
	RoundState<TGameMode> *RoundState<TGameMode>::createRoundState(State<TGameMode> &&state)
	{
		s_RoundStates.push_back(std::make_unique<RoundState<TGameMode>>(std::move(state)));
		return s_RoundStates.back().get();
	}

	template<GameMode TGameMode>
	RoundState<TGameMode>::RoundState()
			: State<TGameMode>()
			, m_Children()
	{
	}

	template<GameMode TGameMode>
	RoundState<TGameMode>::RoundState(State<TGameMode> &&state)
			: State<TGameMode>(std::move(state))
			, m_Children()
	{
	}

	template<GameMode TGameMode>
	bool RoundState<TGameMode>::isTerminal() const
	{
		return false;
	}

	template<GameMode TGameMode>
	void RoundState<TGameMode>::generateChildren(const TurnOptions<TGameMode> &turnOptions)
	{
	}
}

#endif //POKER_ROUNDSTATE_HPP
