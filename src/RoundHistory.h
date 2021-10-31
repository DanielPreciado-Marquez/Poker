#ifndef POKER_ROUNDHISTORY_H
#define POKER_ROUNDHISTORY_H

#include "DealerMove.h"
#include "Enums/GameMode.h"
#include "Hand.h"
#include "PlayerMove.h"
#include "RuleSet/RuleSet.h"

namespace dpm
{

	template<GameMode TGameMode>
	struct RoundHistory
	{
		std::vector<PlayerMove> playerMoves;
		DealerMove <TGameMode> dealerMove;

		explicit RoundHistory(DealerMove <TGameMode> dealerMove);

		void addPlayerMove(const PlayerMove &playerMove, unsigned int index);
	};

	// --- Implementation ---

	template<GameMode TGameMode>
	RoundHistory<TGameMode>::RoundHistory(DealerMove <TGameMode> dealerMove)
			: playerMoves()
			, dealerMove(std::move(dealerMove))
	{
	}

	template<GameMode TGameMode>
	void RoundHistory<TGameMode>::addPlayerMove(const PlayerMove &playerMove, unsigned int index)
	{
		if (playerMoves.size() <= index)
			playerMoves.emplace_back(playerMove);
		else
			playerMoves.emplace(playerMoves.begin() + index, playerMove);
	}
}

#endif //POKER_ROUNDHISTORY_H
