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
		using Hands = std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()>;

	public:
		DealerAction dealerAction;
		std::vector<Card> communityCards;
		Hands hands;

		DealerMove();

		explicit DealerMove(Hands hands);

		explicit DealerMove(std::vector<Card> &&communityCards);

		[[nodiscard]] MoveType getMoveType() const override;

		[[nodiscard]] std::string toString(PlayerIndex playerIndex) const;
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

	template<GameMode TGameMode>
	std::string DealerMove<TGameMode>::toString(const PlayerIndex playerIndex) const
	{
		std::stringstream ss;
		ss << ::dpm::toString(dealerAction);
		if (dealerAction == DealerAction::DrawCommunityCards)
			for (const auto &communityCard: communityCards)
				ss << communityCard.toString();
		if (dealerAction == DealerAction::DrawPlayerCards)
			ss << hands.at(playerIndex).toString();
		return ss.str();
	}
}

#endif //POKER_DEALERMOVE_H
