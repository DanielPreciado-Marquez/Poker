#ifndef POKER_DEALERMOVE_H
#define POKER_DEALERMOVE_H

#include "Card.h"
#include "Enums/DealerAction.h"
#include "Enums/GameMode.h"
#include "Hand.h"
#include "Move.h"
#include "RuleSet/RuleSet.h"
#include "Types/PlayerIndex.h"

namespace dpm
{
	template<GameMode TGameMode>
	struct DealerMove : public Move
	{
	private:
		using Hands = std::array<Hand<TGameMode>, RuleSet<TGameMode>::NUMBER_OF_PLAYERS>;

	public:
		DealerAction dealerAction;
		Card communityCard;
		Hands hands;

		DealerMove();

		explicit DealerMove(Hands hands);

		explicit DealerMove(Card communityCard);

		[[nodiscard]] MoveType getMoveType() const override;

		[[nodiscard]] std::string toString(PlayerIndex playerIndex) const;
	};

	template<GameMode TGameMode>
	DealerMove<TGameMode>::DealerMove()
			: dealerAction(DealerAction::NoAction)
			, communityCard()
			, hands()
	{
	}

	template<GameMode TGameMode>
	DealerMove<TGameMode>::DealerMove(Hands hands)
			: dealerAction(DealerAction::DrawPlayerCards)
			, communityCard()
			, hands(std::move(hands))
	{
	}

	template<GameMode TGameMode>
	DealerMove<TGameMode>::DealerMove(const Card communityCard)
			: dealerAction(DealerAction::DrawCommunityCards)
			, communityCard(communityCard)
			, hands()
	{
	}

	template<GameMode TGameMode>
	MoveType DealerMove<TGameMode>::getMoveType() const
	{
		return MoveType::DealerMove;
	}

	template<GameMode TGameMode>
	std::string DealerMove<TGameMode>::toString(const PlayerIndex playerIndex) const
	{
		std::stringstream ss;
		ss << ::dpm::toString(dealerAction);
		if (dealerAction == DealerAction::DrawCommunityCards)
				ss << communityCard.toString();
		if (dealerAction == DealerAction::DrawPlayerCards)
			ss << hands.at(playerIndex).toString();
		return ss.str();
	}
}

#endif //POKER_DEALERMOVE_H
