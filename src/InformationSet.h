#ifndef KUHN_POKER_INFORMATIONSET_H
#define KUHN_POKER_INFORMATIONSET_H

#include "Enums/GameMode.h"
#include "RuleSet/RuleSet.h"

namespace dpm
{

	template<GameMode TGameMode>
	class InformationSet
	{
	public:
		using TurnStrategy = std::array<float, RuleSet<TGameMode>::getNumberOfPossibleActions()>;

	public:
		static TurnStrategy normalizeStrategy(const TurnStrategy &strategy);

		static void normalizeStrategyInplace(TurnStrategy &strategy);

	public:
		InformationSet();

		[[nodiscard]] const TurnStrategy &getStrategy() const;

		void updateCumulativeRegret(unsigned int moveIndex, float regret);

		void normalizeStrategy();

		TurnStrategy updateStrategy(float reachProbability);

	private:
		TurnStrategy m_Strategy;
		TurnStrategy m_Cumulative_Regrets;
		TurnStrategy m_StrategySum;

	};

	template<GameMode TGameMode>
	typename InformationSet<TGameMode>::TurnStrategy InformationSet<TGameMode>::normalizeStrategy(const TurnStrategy &strategy)
	{
		auto normalizedStrategy = strategy;
		normalizeStrategyInplace(normalizedStrategy);
		return normalizedStrategy;
	}

	template<GameMode TGameMode>
	void InformationSet<TGameMode>::normalizeStrategyInplace(TurnStrategy &strategy)
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

	template<GameMode TGameMode>
	InformationSet<TGameMode>::InformationSet()
			: m_Strategy()
			, m_Cumulative_Regrets()
			, m_StrategySum()
	{
		normalizeStrategy();
	}

	template<GameMode TGameMode>
	const typename InformationSet<TGameMode>::TurnStrategy &InformationSet<TGameMode>::getStrategy() const
	{
		return m_Strategy;
	}

	template<GameMode TGameMode>
	void InformationSet<TGameMode>::updateCumulativeRegret(const unsigned int moveIndex, const float regret)
	{
		m_Cumulative_Regrets.at(moveIndex) += regret;
	}

	template<GameMode TGameMode>
	void InformationSet<TGameMode>::normalizeStrategy()
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

	template<GameMode TGameMode>
	typename InformationSet<TGameMode>::TurnStrategy InformationSet<TGameMode>::updateStrategy(const float reachProbability)
	{
		TurnStrategy strategy;
		for (auto i = 0u; i < m_Cumulative_Regrets.size(); ++i)
			strategy.at(i) = std::max(0.0f, m_Cumulative_Regrets.at(i));
		normalizeStrategyInplace(strategy);
		for (auto i = 0u; i < strategy.size(); ++i)
			m_StrategySum.at(i) += reachProbability * strategy.at(i);
		m_Strategy = normalizeStrategy(m_StrategySum);
		return strategy;
	}
}

#endif //KUHN_POKER_INFORMATIONSET_H
