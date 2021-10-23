#include "InformationSet.h"

namespace dpm
{
	InformationSet::InformationSet()
			: m_Strategy()
			, m_Cumulative_Regrets()
	{
		normalizeStrategy();
	}

	const Strategy &InformationSet::getStrategy()
	{
		normalizeStrategy();
		return m_Strategy;
	}

	void InformationSet::normalizeStrategy()
	{
		auto sum = 0.0f;
		for (const auto probability: m_Strategy)
			sum += probability;
		if (sum > 0)
			for (float &probability: m_Strategy)
				probability = probability / sum;
		else
		{
			const auto uniformProbability = 1.0f / float(m_Strategy.size());
			for (float &probability: m_Strategy)
				probability = uniformProbability;
		}
	}
}
