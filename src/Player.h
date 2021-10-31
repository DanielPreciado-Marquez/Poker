#ifndef KUHN_POKER_PLAYER_H
#define KUHN_POKER_PLAYER_H

#include "Card.h"
#include "History.h"
#include "InformationSet.h"
#include "PlayerMove.h"

namespace dpm
{
	class Player
	{
	public:
		Player();

		Move getNextMove(Card card, const History &history);

		[[nodiscard]] InformationSet &getInformationSet(Card card, const History &history);
	private:
		std::unordered_map<std::string, InformationSet> m_InformationSets;

		std::mt19937 m_Rng;
		std::uniform_real_distribution<float> m_Distribution;

	};
}

#endif //KUHN_POKER_PLAYER_H
