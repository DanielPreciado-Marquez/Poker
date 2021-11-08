#include "PlayerSlot.h"

namespace dpm
{
	PlayerSlot::PlayerSlot()
			: player(nullptr)
			, cash(0)
	{
	}

	PlayerSlot::PlayerSlot(Player *const player)
			: player(player)
			, cash(0)
	{
	}
}
