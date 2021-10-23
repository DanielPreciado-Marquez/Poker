#ifndef KUHN_POKER_INFORMATIONSET_H
#define KUHN_POKER_INFORMATIONSET_H

#include "enums.h"

namespace dpm
{
	using Strategy = std::array<float, Moves::getNumberOfMoves()>;

	class InformationSet
	{
	public:
		static Strategy normalizeStrategy(const Strategy &strategy);

		static void normalizeStrategyInplace(Strategy &strategy);

	public:
		InformationSet();

		[[nodiscard]] const Strategy &getStrategy() const;

		void updateCumulativeRegret(Move move, float regret);

		void normalizeStrategy();

		Strategy updateStrategy(float reachProbability);

	private:
		Strategy m_Strategy;
		Strategy m_Cumulative_Regrets;
		Strategy m_StrategySum;

	private:
	};
}


#endif //KUHN_POKER_INFORMATIONSET_H
