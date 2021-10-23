#include "InformationSet.h"

namespace dpm
{
	Strategy InformationSet::normalizeStrategy(const Strategy &strategy)
	{
		auto normalizedStrategy = strategy;
		normalizeStrategyInplace(normalizedStrategy);
		return normalizedStrategy;
	}

	void InformationSet::normalizeStrategyInplace(Strategy &strategy)
	{
		auto sum = 0.0f;
		for (const auto probability: strategy)
			sum += probability;
		if (sum > 0)
			for (float &probability: strategy)
				probability /= sum;
		else
		{
			const auto uniformProbability = 1.0f / float(strategy.size());
			for (float &probability: strategy)
				probability = uniformProbability;
		}
	}

	InformationSet::InformationSet()
			: m_Strategy()
			, m_Cumulative_Regrets()
			, m_StrategySum()
	{
		normalizeStrategy();
	}

	const Strategy &InformationSet::getStrategy() const
	{
		return m_Strategy;
	}

	void InformationSet::updateCumulativeRegret(const Move move, const float regret)
	{
		m_Cumulative_Regrets.at(move) += regret;
	}

	void InformationSet::normalizeStrategy()
	{
		auto sum = 0.0f;
		for (const auto regret: m_Cumulative_Regrets)
			sum += regret;
		if (sum > 0)
			for (auto i = 0u; i < m_Strategy.size(); ++i)
				m_Strategy.at(i) = m_Cumulative_Regrets.at(i) / sum;
		else
		{
			const auto uniformProbability = 1.0f / float(m_Strategy.size());
			for (float &probability: m_Strategy)
				probability = uniformProbability;
		}
	}

	Strategy InformationSet::updateStrategy(const float reachProbability)
	{
		Strategy strategy;
		for (auto i = 0u; i < m_Cumulative_Regrets.size(); ++i)
			strategy.at(i) = std::max(0.0f, m_Cumulative_Regrets.at(i));
		normalizeStrategyInplace(strategy);
		for (auto i = 0u; i < strategy.size(); ++i)
			m_StrategySum.at(i) += reachProbability * strategy.at(i);
		m_Strategy = normalizeStrategy(m_StrategySum);
		return strategy;
	}
}
