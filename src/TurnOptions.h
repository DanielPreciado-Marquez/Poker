#ifndef POKER_TURNOPTIONS_H
#define POKER_TURNOPTIONS_H

#include "Enums/GameMode.h"
#include "Types/PlayerIndex.h"
#include "RuleSet/RuleSet.h"
#include "DealerMove.h"

namespace dpm
{
	template<GameMode TGameMode>
	class TurnOptions
	{
	private:
		using DealerMove = DealerMove<TGameMode>;
		using RuleSet = RuleSet<TGameMode>;
		using PossiblePlayerMoves = std::array<PlayerMove, NUMBER_OF_PLAYER_ACTIONS>;

	public:
		PlayerIndex nextPlayer;
		PossiblePlayerMoves possiblePlayerMoves;
		DealerMove possibleDealerMove;

		TurnOptions();

		TurnOptions(PlayerIndex playerIndex, PossiblePlayerMoves &&possibleMoves);

		explicit TurnOptions(DealerMove &&dealerMove);
	};

	template<GameMode TGameMode>
	TurnOptions<TGameMode>::TurnOptions()
			: nextPlayer(PlayerIndices::NoPlayer)
			, possiblePlayerMoves()
			, possibleDealerMove()
	{
	}

	template<GameMode TGameMode>
	TurnOptions<TGameMode>::TurnOptions(const PlayerIndex playerIndex, PossiblePlayerMoves &&possibleMoves)
			: nextPlayer(playerIndex)
			, possiblePlayerMoves(std::move(possibleMoves))
			, possibleDealerMove()
	{
	}

	template<GameMode TGameMode>
	TurnOptions<TGameMode>::TurnOptions(DealerMove &&dealerMove)
			: nextPlayer(PlayerIndices::Dealer)
			, possiblePlayerMoves()
			, possibleDealerMove(std::move(dealerMove))
	{
	}
}

#endif //POKER_TURNOPTIONS_H
