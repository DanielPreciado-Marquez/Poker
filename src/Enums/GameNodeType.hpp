#ifndef POKER_GAMENODETYPE_HPP
#define POKER_GAMENODETYPE_HPP

namespace dpm
{
	enum class GameNodeType
	{
		Initial = 0,
		InternalPlayer,
		InternalDealer,
		Terminal
	};
}

#endif //POKER_GAMENODETYPE_HPP
