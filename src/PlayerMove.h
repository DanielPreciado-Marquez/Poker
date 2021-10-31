#ifndef POKER_PLAYERMOVE_H
#define POKER_PLAYERMOVE_H

#include "Enums/PlayerAction.h"
#include "Move.h"
#include "Types/Cash.h"

namespace dpm
{
	struct PlayerMove : public Move
	{
		static PlayerMove NoMove();
		static PlayerMove Bet(Cash stake);
		static PlayerMove Call(Cash stake);
		static PlayerMove Check();
		static PlayerMove Fold();
		static PlayerMove Raise(Cash stake);

		PlayerAction playerAction;
		Cash stake;

		explicit PlayerMove(PlayerAction playerAction = PlayerAction::NoAction, Cash stake = 0);

		[[nodiscard]] MoveType getMoveType() const override;
	};
}

#endif //POKER_PLAYERMOVE_H
