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
		using PossibleDealerMoves = std::vector<DealerMove<TGameMode>>;
		using PossiblePlayerMoves = std::array<PlayerMove, NUMBER_OF_PLAYER_ACTIONS>;

	public:
		PlayerIndex nextPlayer;
		PossiblePlayerMoves possiblePlayerMoves;
		PossibleDealerMoves possibleDealerMoves;

		TurnOptions();

		TurnOptions(PlayerIndex playerIndex, PossiblePlayerMoves &&possibleMoves);

		explicit TurnOptions(PossibleDealerMoves &&dealerMoves);
	};

	template<GameMode TGameMode>
	TurnOptions<TGameMode>::TurnOptions()
			: nextPlayer(PlayerIndices::NoPlayer)
			, possiblePlayerMoves()
			, possibleDealerMoves()
	{
	}

	template<GameMode TGameMode>
	TurnOptions<TGameMode>::TurnOptions(const PlayerIndex playerIndex, PossiblePlayerMoves &&possibleMoves)
			: nextPlayer(playerIndex)
			, possiblePlayerMoves(std::move(possibleMoves))
			, possibleDealerMoves()
	{
	}

	template<GameMode TGameMode>
	TurnOptions<TGameMode>::TurnOptions(PossibleDealerMoves &&dealerMoves)
			: nextPlayer(PlayerIndices::Dealer)
			, possiblePlayerMoves()
			, possibleDealerMoves(std::move(dealerMoves))
	{
	}
}

#endif //POKER_TURNOPTIONS_H
