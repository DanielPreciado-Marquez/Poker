#include "Outcome.h"

namespace dpm
{
	Outcome::Outcome(PlayerIndex winner, Stake stake)
			: winner(winner)
			, stake(stake)
	{
	}

	std::ostream &operator<<(std::ostream &ostream, const Outcome &outcome)
	{
		return ostream << "Outcome[Winner: " << PlayerIndices::toString(outcome.winner) << ", Stake: "
		               << std::to_string(outcome.stake) << "]";
	}
}
