#include "State.h"

namespace dpm
{
	State::State()
			: cards({Cards::NoCard, Cards::NoCard})
			, nextPlayer(PlayerIndices::NoPlayer)
			, turn(0)
			, stakes({0, 0})
	{
	}

	State::State(const Hands &cards, const PlayerIndex nextPlayer, const Turn turn,
	             const Stake stakePlayer1, const Stake stakePlayer2)
			: cards(cards)
			, nextPlayer(nextPlayer)
			, turn(turn)
			, stakes({stakePlayer1, stakePlayer2})
	{
	}
}
