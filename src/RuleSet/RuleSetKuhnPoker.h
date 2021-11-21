#ifndef KUHN_POKER_RULESETKUHNPOKER_H
#define KUHN_POKER_RULESETKUHNPOKER_H

#include "Card.h"
#include "Enums/PlayerAction.h"
#include "PlayerMove.h"
#include "RuleSet/RuleSet.h"
#include "Types/Cash.h"
#include "Types/Turn.h"

namespace dpm
{
	template<>
	class RuleSet<GameMode::KuhnPoker>
	{
	public:

		static constexpr std::array<Card, 3> getAllCards();

		static constexpr bool CAN_CHECK_IN_FIRST_ROUND = true;

		static constexpr unsigned int NUMBER_OF_CARDS = 3u;

		static constexpr unsigned int NUMBER_OF_CARDS_PER_PLAYER = 1u;
		static constexpr unsigned int getNumberOfCardsPerPlayer();

		static constexpr unsigned int NUMBER_OF_POSSIBLE_COMMUNITY_CARDS = 0u;

		static constexpr unsigned int NUMBER_OF_COMMUNITY_CARDS = 0u;

		static constexpr unsigned int NUMBER_OF_HAND_COMBINATIONS = 6u;

		static constexpr unsigned int NUMBER_OF_PLAYERS = 2u;
		static constexpr unsigned int getNumberOfPlayers();

		static constexpr unsigned int NUMBER_OF_RAISES = 0u;

		static constexpr unsigned int NUMBER_OF_ROUNDS = 1u;

		static constexpr std::array<Card, NUMBER_OF_CARDS> ALL_CARDS = {Card::ClubJack(), Card::ClubQueen(), Card::ClubKing()};
		static constexpr std::array<unsigned int, NUMBER_OF_ROUNDS> NUMBER_OF_COMMUNITY_CARDS_PER_ROUND = {0u};

	public:
		explicit RuleSet(Cash smallBlind = 1, Cash bigBlind = 1);

		[[nodiscard]] Cash getSmallBlind() const;

		[[nodiscard]] Cash getBigBlind() const;

	private:
		Cash m_SmallBlind;
		Cash m_BigBlind;

	};

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfPlayers()
	{
		return 2;
	}

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfCardsPerPlayer()
	{
		return 1;
	}

	constexpr std::array<Card, 3> RuleSet<GameMode::KuhnPoker>::getAllCards()
	{
		return {Card::ClubJack(), Card::ClubQueen(), Card::ClubKing()};
	}

	RuleSet<GameMode::KuhnPoker>::RuleSet(const Cash smallBlind, const Cash bigBlind)
			: m_BigBlind(bigBlind)
			, m_SmallBlind(smallBlind)
	{
	}

	Cash RuleSet<GameMode::KuhnPoker>::getSmallBlind() const
	{
		return m_SmallBlind;
	}

	Cash RuleSet<GameMode::KuhnPoker>::getBigBlind() const
	{
		return m_BigBlind;
	}


}

#endif //KUHN_POKER_RULESETKUHNPOKER_H
