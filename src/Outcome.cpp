#include "Outcome.h"

namespace dpm
{
	Outcome::Outcome(const PlayerIndex winner, const Cash stake)
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
