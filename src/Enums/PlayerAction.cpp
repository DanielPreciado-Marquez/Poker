#include "PlayerAction.h"

namespace dpm
{
	PlayerActionIndex getPlayerActionIndex(const PlayerAction playerAction)
	{
		return static_cast<PlayerActionIndex>(playerAction);
	}

	std::string toString(PlayerAction playerAction)
	{
		switch (playerAction)
		{
			case PlayerAction::NoAction:
				return "NoAction";
			case PlayerAction::Check:
				return "Check/Call";
			case PlayerAction::Bet:
				return "Bet/Raise";
			case PlayerAction::Fold:
				return "Fold";
			default:
				return "UnknownAction";
		}
	}
}
