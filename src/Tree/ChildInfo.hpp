#ifndef POKER_CHILDINFO_HPP
#define POKER_CHILDINFO_HPP

#include "Enums/GameMode.h"
#include "Enums/GameNodeType.hpp"

namespace dpm
{
	template<GameMode TGameMode>
	struct State;

	template<GameMode TGameMode>
	struct ChildInfo
	{
		State<TGameMode> *state;
		PlayerMove playerMove;
		DealerMove<TGameMode> dealerMove;

		ChildInfo();
		ChildInfo(State<TGameMode> *state, PlayerMove &&playerMove);
		ChildInfo(State<TGameMode> *state, DealerMove<TGameMode> &&dealerMove);
	};

	template<GameMode TGameMode>
	ChildInfo<TGameMode>::ChildInfo()
			: state(nullptr)
			, playerMove()
			, dealerMove()
	{
	}

	template<GameMode TGameMode>
	ChildInfo<TGameMode>::ChildInfo(State<TGameMode> *const state, PlayerMove &&playerMove)
		: state(state)
		, playerMove(std::move(playerMove))
		, dealerMove()
	{
	}

	template<GameMode TGameMode>
	ChildInfo<TGameMode>::ChildInfo(State<TGameMode> *const state, DealerMove<TGameMode> &&dealerMove)
			: state(state)
			, playerMove()
			, dealerMove(std::move(dealerMove))
	{
	}
}

#endif //POKER_CHILDINFO_HPP
