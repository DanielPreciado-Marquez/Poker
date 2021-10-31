#ifndef KUHN_POKER_TURN_H
#define KUHN_POKER_TURN_H

namespace dpm
{
	using Round = std::int8_t;

	namespace Rounds
	{
		enum : Round
		{
			Round1 = 0,
			Round2 = 1,
			End = 2
		};
	}
}

#endif //KUHN_POKER_TURN_H
