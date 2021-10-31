#include "PlayerIndex.h"

namespace dpm::PlayerIndices
{
	std::string toString(PlayerIndex playerIndex)
	{
		switch (playerIndex)
		{
			case NoPlayer:
				return "NoPlayer";
			case Dealer:
				return "Dealer";
			default:
				return "Player" + std::to_string(playerIndex);
		}
	}
}
