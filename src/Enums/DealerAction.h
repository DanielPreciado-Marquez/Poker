#ifndef POKER_DEALERACTION_H
#define POKER_DEALERACTION_H

namespace dpm
{
	enum class DealerAction
	{
		NoAction,
		DrawPlayerCards,
		DrawCommunityCards
	};

	[[nodiscard]] std::string toString(DealerAction dealerAction);
}

#endif //POKER_DEALERACTION_H
