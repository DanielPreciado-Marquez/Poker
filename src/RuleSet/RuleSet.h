#ifndef KUHN_POKER_RULESET_H
#define KUHN_POKER_RULESET_H

#include "Enums/GameMode.h"
#include "Types/Cash.h"

namespace dpm
{
	template<GameMode TGameMode>
	class RuleSet
	{
		static constexpr bool CAN_CHECK_IN_FIRST_ROUND = true;
		static constexpr unsigned int NUMBER_OF_CARDS = 3u;
		static constexpr unsigned int NUMBER_OF_CARDS_PER_PLAYER = 1u;
		static constexpr unsigned int NUMBER_OF_COMMUNITY_CARDS = 0u;
		static constexpr unsigned int NUMBER_OF_HAND_COMBINATIONS = 6u;
		static constexpr unsigned int NUMBER_OF_PLAYERS = 2u;
		static constexpr unsigned int NUMBER_OF_POSSIBLE_COMMUNITY_CARDS = 0u;
		static constexpr unsigned int NUMBER_OF_RAISES = 0u;
		static constexpr unsigned int NUMBER_OF_ROUNDS = 1u;
		static constexpr std::array<Card, NUMBER_OF_CARDS> ALL_CARDS = {Card::ClubJack(), Card::ClubQueen(), Card::ClubKing()};
		static constexpr std::array<unsigned int, NUMBER_OF_ROUNDS> NUMBER_OF_COMMUNITY_CARDS_PER_ROUND = {0u};

		[[nodiscard]]
		constexpr Cash getSmallBlind() const { return 1; }

		[[nodiscard]]
		constexpr Cash getBigBlind() const { return 2; }
	};
}

#endif //KUHN_POKER_RULESET_H
