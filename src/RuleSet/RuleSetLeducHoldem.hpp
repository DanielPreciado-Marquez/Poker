#ifndef DPMPOKER_RULESETLEDUCHOLDEM_HPP
#define DPMPOKER_RULESETLEDUCHOLDEM_HPP

#include "Card.h"
#include "Enums/PlayerAction.h"
#include "PlayerMove.h"
#include "RuleSet/RuleSet.h"
#include "Types/Cash.h"
#include "Types/Turn.h"

namespace dpm
{
	template<>
	class RuleSet<GameMode::LeducHoldem>
	{
	public:
		static constexpr bool CAN_CHECK_IN_FIRST_ROUND = true;
		static constexpr unsigned int MAX_DEALER_MOVES_PER_ROUND = 1u;
		static constexpr unsigned int NUMBER_OF_CARDS = 6u;
		static constexpr unsigned int NUMBER_OF_CARDS_PER_PLAYER = 1u;
		static constexpr unsigned int NUMBER_OF_POSSIBLE_COMMUNITY_CARDS = 4u;
		static constexpr unsigned int NUMBER_OF_COMMUNITY_CARDS = 1u;
		static constexpr unsigned int NUMBER_OF_HAND_COMBINATIONS = 30u;
		static constexpr unsigned int NUMBER_OF_PLAYERS = 2u;
		static constexpr unsigned int NUMBER_OF_RAISES = 2u;
		static constexpr unsigned int NUMBER_OF_ROUNDS = 2u;

		static constexpr std::array<Card, NUMBER_OF_CARDS> ALL_CARDS = {Card::ClubEight(), Card::ClubNine(),
		                                                                Card::ClubTen(), Card::ClubJack(),
		                                                                Card::ClubQueen(), Card::ClubKing()};
		static constexpr std::array<unsigned int, NUMBER_OF_ROUNDS> NUMBER_OF_COMMUNITY_CARDS_PER_ROUND = {1u, 0u};
		static constexpr std::array<Cash, NUMBER_OF_ROUNDS> RAISES = {2, 4};

	public:
		explicit RuleSet(Cash smallBlind = 1, Cash bigBlind = 1);

		[[nodiscard]] Cash getSmallBlind() const;

		[[nodiscard]] Cash getBigBlind() const;

	private:
		Cash m_SmallBlind;
		Cash m_BigBlind;

	};

	RuleSet<GameMode::LeducHoldem>::RuleSet(const Cash smallBlind, const Cash bigBlind)
			: m_BigBlind(bigBlind)
			, m_SmallBlind(smallBlind)
	{
	}

	Cash RuleSet<GameMode::LeducHoldem>::getSmallBlind() const
	{
		return m_SmallBlind;
	}

	Cash RuleSet<GameMode::LeducHoldem>::getBigBlind() const
	{
		return m_BigBlind;
	}

}


#endif //DPMPOKER_RULESETLEDUCHOLDEM_HPP
