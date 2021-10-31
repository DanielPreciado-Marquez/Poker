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
		static constexpr unsigned int getNumberOfPlayers();

		static constexpr unsigned int getNumberOfCards();

		static constexpr unsigned int getNumberOfCardsPerPlayer();

		static constexpr unsigned int getNumberOfCommunityCards();

		static constexpr std::array<Card, 3> getAllCards();

		static constexpr unsigned int getNumberOfPossibleActions();

		static constexpr unsigned int getNumberOfRounds();

		static constexpr int getNumberOfRaises();

		static constexpr bool canCheckInFirstRound();

		static unsigned int getNumberOfCommunityCards(unsigned int roundNumber);

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

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfCards()
	{
		return 3;
	}

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfCardsPerPlayer()
	{
		return 1;
	}

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfCommunityCards()
	{
		return 0;
	}

	constexpr std::array<Card, 3> RuleSet<GameMode::KuhnPoker>::getAllCards()
	{
		return {Card::ClubJack(), Card::ClubQueen(), Card::ClubKing()};
	}

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfPossibleActions()
	{
		return 2;
	}

	constexpr unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfRounds()
	{
		return 1;
	}

	constexpr int RuleSet<GameMode::KuhnPoker>::getNumberOfRaises()
	{
		return 0;
	}

	constexpr bool RuleSet<GameMode::KuhnPoker>::canCheckInFirstRound()
	{
		return true;
	}

	unsigned int RuleSet<GameMode::KuhnPoker>::getNumberOfCommunityCards(const unsigned int roundNumber)
	{
		return 0;
	}

//	TurnOptions<GameMode::KuhnPoker> RuleSet<GameMode::KuhnPoker>::getTurnOptions(const History &history)
//	{
//		const auto roundNumber = history.moves.size();
//		switch (roundNumber)
//		{
//			case 0:
//				return TurnOption::endOfRound();
//			case 1:
//			{
//				const auto &roundHistory = history.moves.at(0);
//				switch (roundHistory.size())
//				{
//					case 0:
//						return TurnOption::nextOptions({PlayerMove::Check(), PlayerMove::Bet(1)});
//					case 1:
//					{
//						switch (roundHistory.at(0).playerAction)
//						{
//							case PlayerAction::Bet:
//								return TurnOption::nextOptions({PlayerMove::Fold(), PlayerMove::Call(1)});
//							case PlayerAction::Check:
//								return TurnOption::nextOptions({PlayerMove::Check(), PlayerMove::Bet(1)});
//							default:
//								return TurnOption::endOfGame();
//						}
//					}
//					default:
//						return TurnOption::endOfRound();
//				}
//			}
//			case 2:
//				if (history.moves.at(0).at(0).playerAction == PlayerAction::Check &&
//				    history.moves.at(0).at(1).playerAction == PlayerAction::Bet)
//					return TurnOption::nextOptions({PlayerMove::Fold(), PlayerMove::Call(1)});
//				else
//					return TurnOption::endOfGame();
//			default:
//				return TurnOption::endOfGame();
//		}
//	}

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
