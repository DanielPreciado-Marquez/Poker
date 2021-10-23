#ifndef KUHN_POKER_STATE_H
#define KUHN_POKER_STATE_H

#include "enums.h"

namespace dpm
{
	struct State
	{
	public:
		Hands cards;
		PlayerIndex nextPlayer;
		Turn turn;
		std::array<Stake, PlayerIndices::getNumberOfPlayers()> stakes;

	public:
		State();

		State(const Hands &cards, PlayerIndex nextPlayer, Turn turn, Stake stakePlayer1, Stake stakePlayer2);
	};
}


#endif //KUHN_POKER_STATE_H
