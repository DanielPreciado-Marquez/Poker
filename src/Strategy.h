#ifndef POKER_STRATEGY_H
#define POKER_STRATEGY_H

#include "Enums/GameMode.h"
#include "InformationSet.h"
#include "StrategyBase.h"

namespace dpm
{
	template<GameMode TGameMode>
	class Strategy : public StrategyBase
	{
	public:
		Strategy();

		InformationSet<TGameMode> &getInformationSet(PlayerIndex playerIndex,
		                                             const History<TGameMode> &history,
		                                             const TurnOptions<TGameMode> &turnOptions);

	private:
		std::unordered_map<std::string, InformationSet<TGameMode>> m_InformationSets;
	};

	template<GameMode TGameMode>
	Strategy<TGameMode>::Strategy()
			: StrategyBase()
			, m_InformationSets()
	{
	}

	template<GameMode TGameMode>
	InformationSet<TGameMode> &Strategy<TGameMode>::getInformationSet(const PlayerIndex playerIndex,
	                                                                  const History<TGameMode> &history,
	                                                                  const TurnOptions<TGameMode> &turnOptions)
	{
		const auto key = history.toString(playerIndex);
		auto informationSetIterator = m_InformationSets.find(key);
		if (informationSetIterator == m_InformationSets.end())
			informationSetIterator = m_InformationSets.emplace(key, InformationSet<TGameMode>(turnOptions)).first;
		return informationSetIterator->second;
	}
}

#endif //POKER_STRATEGY_H