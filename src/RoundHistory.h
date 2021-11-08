#ifndef POKER_ROUNDHISTORY_H
#define POKER_ROUNDHISTORY_H

#include "DealerMove.h"
#include "Enums/GameMode.h"
#include "Hand.h"
#include "PlayerMove.h"
#include "RuleSet/RuleSet.h"
#include "Types/PlayerIndex.h"

namespace dpm
{

	template<GameMode TGameMode>
	struct RoundHistory
	{
		std::vector<PlayerMove> playerMoves;
		DealerMove <TGameMode> dealerMove;

		explicit RoundHistory(DealerMove <TGameMode> dealerMove);

		void addPlayerMove(const PlayerMove &playerMove, unsigned int index);

		[[nodiscard]] std::string toString(PlayerIndex playerIndex) const;

		[[nodiscard]] std::string toString(PlayerIndex playerIndex, unsigned int numberMoves) const;
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

	template<GameMode TGameMode>
	std::string RoundHistory<TGameMode>::toString(const PlayerIndex playerIndex) const
	{
		std::stringstream ss;
		ss << dealerMove.toString(playerIndex);
		for (const auto &playerMove: playerMoves)
			ss << playerMove.toString();
		return ss.str();
	}

	template<GameMode TGameMode>
	std::string RoundHistory<TGameMode>::toString(const PlayerIndex playerIndex, const unsigned int numberMoves) const
	{
		std::stringstream ss;
		ss << dealerMove.toString(playerIndex);
		for (auto i = 0u; i < numberMoves; ++i)
			ss << playerMoves.at(i).toString();
		return ss.str();
	}
}

#endif //POKER_ROUNDHISTORY_H
