#ifndef KUHN_POKER_PLAYERINDEX_H
#define KUHN_POKER_PLAYERINDEX_H

namespace dpm
{
	using PlayerIndex = std::int8_t;

	namespace PlayerIndices
	{
		enum : PlayerIndex
		{
			NoPlayer = -2,
			Dealer = -1,
			Player1 = 0,
			Player2 = 1
		};

		std::string toString(PlayerIndex playerIndex);
	}
}

#endif //KUHN_POKER_PLAYERINDEX_H
