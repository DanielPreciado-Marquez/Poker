#ifndef KUHN_POKER_INFORMATIONSET_H
#define KUHN_POKER_INFORMATIONSET_H

#include "enums.h"

namespace dpm
{
	using Strategy = std::array<float, Moves::getNumberOfMoves()>;

	class InformationSet
	{
	public:
		InformationSet();

		[[nodiscard]] const Strategy &getStrategy();

	private:
		Strategy m_Strategy;
		Strategy m_Cumulative_Regrets;

	private:
		void normalizeStrategy();
	};
}



#endif //KUHN_POKER_INFORMATIONSET_H
