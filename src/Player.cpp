#include "Player.h"

namespace dpm
{
	Player::Player()
		: m_InformationSets()
		, m_Rng(std::random_device()())
		, m_Distribution(0.0f, 1.0f)
	{
	}

	Move Player::getNextMove(const Card card, const History &history)
	{
		auto &informationSet = getInformationSet(card, history);
		const auto &strategy = informationSet.getStrategy();
		const float decision = m_Distribution(m_Rng);
		auto move = static_cast<Move>(0);
		auto strategySum = strategy.at(move);
		while (decision > strategySum)
		{
			strategySum += strategy.at(move);
			++move;
		}
		return move;
	}

	InformationSet &Player::getInformationSet(Card card, const History &history)
	{
		const auto key = Cards::toString(card)
		                 + std::to_string(history.at(0))
		                 + std::to_string(history.at(1))
		                 + std::to_string(history.at(2));
		auto informationSetIterator = m_InformationSets.find(key);
		if (informationSetIterator == m_InformationSets.end())
			informationSetIterator = m_InformationSets.emplace(key, InformationSet()).first;
		return informationSetIterator->second;
	}
}
