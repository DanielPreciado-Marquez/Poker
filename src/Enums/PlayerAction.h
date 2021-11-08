#ifndef KUHN_POKER_PLAYERACTION_H
#define KUHN_POKER_PLAYERACTION_H

namespace dpm
{
	using PlayerActionIndex = std::int8_t;

	enum class PlayerAction : PlayerActionIndex
	{
		NoAction = -1,

		Check = 0,
		Bet = 1,

		Call = 0,
		Raise = 1,
		Fold = 2
	};

	template<PlayerAction TPlayerAction>
	constexpr PlayerActionIndex getPlayerActionIndex()
	{
		return static_cast<PlayerActionIndex>(TPlayerAction);
	}

	PlayerActionIndex getPlayerActionIndex(PlayerAction playerAction);

	std::string toString(PlayerAction playerAction);
}

#endif //KUHN_POKER_PLAYERACTION_H
