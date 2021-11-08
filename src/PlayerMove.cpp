#include "PlayerMove.h"

namespace dpm
{
	PlayerMove PlayerMove::NoMove()
	{
		return PlayerMove{};
	}

	PlayerMove PlayerMove::Bet(const Cash stake)
	{
		return PlayerMove{PlayerAction::Bet, stake};
	}

	PlayerMove PlayerMove::Call(const Cash stake)
	{
		return PlayerMove{PlayerAction::Call, stake};
	}

	PlayerMove PlayerMove::Check()
	{
		return PlayerMove{PlayerAction::Check};
	}

	PlayerMove PlayerMove::Fold()
	{
		return PlayerMove{PlayerAction::Fold};
	}

	PlayerMove PlayerMove::Raise(const Cash stake)
	{
		return PlayerMove{PlayerAction::Raise, stake};
	}

	PlayerMove::PlayerMove(const PlayerAction playerAction, const Cash stake)
			: Move()
			, playerAction(playerAction)
			, stake(stake)
	{
	}

	std::string PlayerMove::toString() const
	{
		return ::dpm::toString(playerAction) + std::to_string(stake);
	}

	MoveType PlayerMove::getMoveType() const
	{
		return MoveType::PlayerMove;
	}
}
