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
		using Children = std::array<ChildInfo<TGameMode>, RuleSet<TGameMode>::NUMBER_OF_POSSIBLE_COMMUNITY_CARDS>;

	public:
		static RoundState *createRoundState(State<TGameMode> &&state);

	public:
		RoundState();

		RoundState(const RoundState &gameState) = default;

		explicit RoundState(State<TGameMode> &&state);

		[[nodiscard]]
		GameStateType getGameStateType() const override;

		[[nodiscard]] const Children &getChildren() const;

		[[nodiscard]] unsigned int getNumberOfChildren() const;

		void generateChildren(const TurnOptions<TGameMode> &turnOptions);

	private:
		static std::vector<std::unique_ptr<RoundState<TGameMode>>> s_RoundStates;

	private:
		Children m_Children;
		unsigned int m_NumberChildren;

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
			, m_NumberChildren()
	{
	}

	template<GameMode TGameMode>
	RoundState<TGameMode>::RoundState(State<TGameMode> &&state)
			: State<TGameMode>(std::move(state))
			, m_Children()
			, m_NumberChildren()
	{
	}

	template<GameMode TGameMode>
	GameStateType RoundState<TGameMode>::getGameStateType() const
	{
		return GameStateType::DEALER_MOVE;
	}

	template<GameMode TGameMode>
	const typename RoundState<TGameMode>::Children &RoundState<TGameMode>::getChildren() const
	{
		return m_Children;
	}

	template<GameMode TGameMode>
	unsigned int RoundState<TGameMode>::getNumberOfChildren() const
	{
		return m_NumberChildren;
	}

	template<GameMode TGameMode>
	void RoundState<TGameMode>::generateChildren(const TurnOptions<TGameMode> &turnOptions)
	{
		m_NumberChildren = turnOptions.possibleDealerMoves.size();
		for (auto i = 0u; i < m_NumberChildren; ++i)
		{
			auto &dealerMove = turnOptions.possibleDealerMoves.at(i);
			this->generateChild(&m_Children.at(i), std::move(dealerMove), PlayerIndices::Dealer);
		}
	}
}

#endif //POKER_ROUNDSTATE_HPP
