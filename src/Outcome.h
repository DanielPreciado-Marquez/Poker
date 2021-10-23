#ifndef KUHN_POKER_OUTCOME_H
#define KUHN_POKER_OUTCOME_H

#include "enums.h"

namespace dpm
{
	struct Outcome
	{
		PlayerIndex winner;
		Stake stake;

		Outcome(PlayerIndex winner, Stake stake);
	};

	std::ostream &operator<<(std::ostream &ostream, const Outcome &outcome);
}

#endif //KUHN_POKER_OUTCOME_H
