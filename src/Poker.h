#ifndef KUHN_POKER_POKER_H
#define KUHN_POKER_POKER_H

#include "Enums/GameMode.h"
#include "RuleSet/RuleSets.h"
#include "Tree/RootNode.h"

namespace dpm
{
	template<GameMode TGameMode>
	class Poker
	{
	public:
		Poker();

		Poker(RuleSet<TGameMode> &&ruleSet);

	private:
		RootNode<TGameMode> m_GameTree;
		RuleSet<TGameMode> m_RuleSet;
	};

	template<GameMode TGameMode>
	Poker<TGameMode>::Poker()
			: m_GameTree()
			, m_RuleSet()
	{
		m_GameTree.generateChildren(&m_RuleSet);
	}

	template<GameMode TGameMode>
	Poker<TGameMode>::Poker(RuleSet<TGameMode> &&ruleSet)
			: m_GameTree()
			, m_RuleSet(std::move(ruleSet))
	{
		m_GameTree.generateChildren(&m_RuleSet);
	}
}

#endif //KUHN_POKER_POKER_H
