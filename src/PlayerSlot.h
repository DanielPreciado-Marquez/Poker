#ifndef POKER_PLAYERSLOT_H
#define POKER_PLAYERSLOT_H

#include "Player.h"
#include "Types/Cash.h"

namespace dpm
{
	struct PlayerSlot
	{
		Player *player;
		Cash cash;

		PlayerSlot();

		explicit PlayerSlot(Player *player);
	};
}


#endif //POKER_PLAYERSLOT_H
