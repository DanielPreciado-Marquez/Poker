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
		using TurnStrategy = std::array<float, NUMBER_OF_PLAYER_ACTIONS>;
		using PossiblePlayerActions = std::array<PlayerAction, NUMBER_OF_PLAYER_ACTIONS>;

	public:
		explicit InformationSet(const PossiblePlayerActions &possiblePlayerActions);

		[[nodiscard]] const TurnStrategy &getStrategy() const;

		void updateCumulativeRegret(unsigned int moveIndex, float regret);

		TurnStrategy updateStrategy(float reachProbability);

	private:
		TurnStrategy m_Strategy;
		TurnStrategy m_Cumulative_Regrets;
		TurnStrategy m_StrategySum;

		PossiblePlayerActions m_PlayerActions;

	private:
		void applyInitialStrategy(TurnStrategy &turnStrategy) const;

		void normalizeStrategyInplace(TurnStrategy &strategy);

		TurnStrategy normalizeStrategy(const TurnStrategy &strategy);

	};

	template<GameMode TGameMode>
	InformationSet<TGameMode>::InformationSet(const PossiblePlayerActions &possiblePlayerActions)
			: m_Strategy()
			, m_Cumulative_Regrets()
			, m_StrategySum()
			, m_PlayerActions(possiblePlayerActions)
	{
		applyInitialStrategy(m_Strategy);
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
	typename InformationSet<TGameMode>::TurnStrategy
	InformationSet<TGameMode>::updateStrategy(const float reachProbability)
	{
		TurnStrategy strategy;
		auto sum = 0.0f;
		for (auto i = 0u; i < m_Cumulative_Regrets.size(); ++i)
			strategy.at(i) = std::max(0.0f, m_Cumulative_Regrets.at(i));
		normalizeStrategyInplace(strategy);
		for (auto i = 0u; i < strategy.size(); ++i)
			m_StrategySum.at(i) += reachProbability * strategy.at(i);
		m_Strategy = normalizeStrategy(m_StrategySum);
		return strategy;
	}

	template<GameMode TGameMode>
	void InformationSet<TGameMode>::applyInitialStrategy(TurnStrategy &turnStrategy) const
	{
		auto numActions = 0.0f;
		for (auto &playerAction: m_PlayerActions)
			if (playerAction != PlayerAction::NoAction)
				++numActions;
		auto probability = 1.0f / numActions;
		for (auto i = 0u; i < m_PlayerActions.size(); ++i)
			if (m_PlayerActions.at(i) != PlayerAction::NoAction)
				turnStrategy.at(i) = probability;
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
			applyInitialStrategy(strategy);
	}

	template<GameMode TGameMode>
	typename InformationSet<TGameMode>::TurnStrategy
	InformationSet<TGameMode>::normalizeStrategy(const TurnStrategy &strategy)
	{
		auto normalizedStrategy = strategy;
		normalizeStrategyInplace(normalizedStrategy);
		return normalizedStrategy;
	}
}

#endif //KUHN_POKER_INFORMATIONSET_H
