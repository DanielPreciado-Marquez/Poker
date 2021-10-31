#ifndef POKER_DEALERMOVE_H
#define POKER_DEALERMOVE_H

#include "Card.h"
#include "Enums/DealerAction.h"
#include "Enums/GameMode.h"
#include "Hand.h"
#include "Move.h"
#include "RuleSet/RuleSet.h"

namespace dpm
{
	template<GameMode TGameMode>
	struct DealerMove : public Move
	{
	private:
		using Hands = std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()>;

	public:
		DealerAction dealerAction;
		std::vector<Card> communityCards;
		Hands hands;

		DealerMove();

		explicit DealerMove(Hands hands);

		explicit DealerMove(std::vector<Card> &&communityCards);

		[[nodiscard]] MoveType getMoveType() const override;
	};

	template<GameMode TGameMode>
	DealerMove<TGameMode>::DealerMove()
			: dealerAction(DealerAction::NoAction)
			, communityCards()
			, hands()
	{
	}

	template<GameMode TGameMode>
	DealerMove<TGameMode>::DealerMove(Hands hands)
			: dealerAction(DealerAction::DrawPlayerCards)
			, communityCards()
			, hands(std::move(hands))
	{
	}

	template<GameMode TGameMode>
	DealerMove<TGameMode>::DealerMove(std::vector<Card> &&communityCards)
			: dealerAction(DealerAction::DrawCommunityCards)
			, communityCards(std::move(communityCards))
			, hands()
	{
	}

	template<GameMode TGameMode>
	MoveType DealerMove<TGameMode>::getMoveType() const
	{
		return MoveType::DealerMove;
	}
}

#endif //POKER_DEALERMOVE_H
