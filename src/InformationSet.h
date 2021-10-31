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
		using Strategy = std::array<float, RuleSet<TGameMode>::getNumberOfPossibleActions()>;

	public:
		static Strategy normalizeStrategy(const Strategy &strategy);

		static void normalizeStrategyInplace(Strategy &strategy);

	public:
		InformationSet();

		[[nodiscard]] const Strategy &getStrategy() const;

		void updateCumulativeRegret(PlayerMove move, float regret);

		void normalizeStrategy();

		Strategy updateStrategy(float reachProbability);

	private:
		Strategy m_Strategy;
		Strategy m_Cumulative_Regrets;
		Strategy m_StrategySum;

	};

	template<GameMode TGameMode>
	typename InformationSet<TGameMode>::Strategy InformationSet<TGameMode>::normalizeStrategy(const Strategy &strategy)
	{
		auto normalizedStrategy = strategy;
		normalizeStrategyInplace(normalizedStrategy);
		return normalizedStrategy;
	}

	template<GameMode TGameMode>
	void InformationSet<TGameMode>::normalizeStrategyInplace(Strategy &strategy)
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
	const typename InformationSet<TGameMode>::Strategy &InformationSet<TGameMode>::getStrategy() const
	{
		return m_Strategy;
	}

	template<GameMode TGameMode>
	void InformationSet<TGameMode>::updateCumulativeRegret(const PlayerMove move, const float regret)
	{
		m_Cumulative_Regrets.at(move) += regret;
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
	typename InformationSet<TGameMode>::Strategy InformationSet<TGameMode>::updateStrategy(const float reachProbability)
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

#endif //KUHN_POKER_INFORMATIONSET_H
