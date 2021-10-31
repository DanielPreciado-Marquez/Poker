#ifndef KUHN_POKER_OUTCOME_H
#define KUHN_POKER_OUTCOME_H

#include "Types/Cash.h"
#include "Types/PlayerIndex.h"

namespace dpm
{
	struct Outcome
	{
		PlayerIndex winner;
		Cash stake;

		Outcome(PlayerIndex winner, Cash stake);
	};

	std::ostream &operator<<(std::ostream &ostream, const Outcome &outcome);
}

#endif //KUHN_POKER_OUTCOME_H
