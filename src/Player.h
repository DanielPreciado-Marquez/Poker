#ifndef KUHN_POKER_PLAYER_H
#define KUHN_POKER_PLAYER_H

#include "Card.h"
#include "History.h"
#include "InformationSet.h"
#include "PlayerMove.h"
#include "Strategy.h"

namespace dpm
{
	class Player
	{
	public:
		Player();

		template<GameMode TGameMode>
		[[nodiscard]] PlayerMove getNextMove(PlayerIndex playerIndex, const History<TGameMode> &history);

		template<GameMode TGameMode>
		[[nodiscard]] InformationSet<TGameMode> &getInformationSet(PlayerIndex playerIndex,
		                                                           const History<TGameMode> &history,
		                                                           const TurnOptions<TGameMode> &turnOptions);

	private:
		std::unordered_map<GameMode, std::unique_ptr<StrategyBase>> m_Strategies;

		std::mt19937 m_Rng;
		std::uniform_real_distribution<float> m_Distribution;
	};

	template<GameMode TGameMode>
	PlayerMove Player::getNextMove(const PlayerIndex playerIndex, const History<TGameMode> &history)
	{
		// TODO stakes
		auto &informationSet = getInformationSet(playerIndex, history);
		const auto &strategy = informationSet.getStrategy();
		const float decision = m_Distribution(m_Rng);
		auto moveIndex = 0;
		auto strategySum = strategy.at(moveIndex);
		while (decision > strategySum)
		{
			strategySum += strategy.at(moveIndex);
			++moveIndex;
		}
		// TODO map index to move
		return PlayerMove{};
	}

	template<GameMode TGameMode>
	InformationSet<TGameMode> &Player::getInformationSet(const PlayerIndex playerIndex,
	                                                     const History<TGameMode> &history,
	                                                     const TurnOptions<TGameMode> &turnOptions)
	{
		auto strategyItr = m_Strategies.find(TGameMode);
		if (strategyItr == m_Strategies.end())
			strategyItr = m_Strategies.emplace(TGameMode, std::make_unique<Strategy<TGameMode>>()).first;
		auto strategy = dynamic_cast<Strategy<TGameMode> *>(strategyItr->second.get());
		return strategy->getInformationSet(playerIndex, history, turnOptions);
	}

}

#endif //KUHN_POKER_PLAYER_H
