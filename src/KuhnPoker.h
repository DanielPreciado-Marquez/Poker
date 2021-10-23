#ifndef KUHN_POKER_KUHNPOKER_H
#define KUHN_POKER_KUHNPOKER_H

#include "Player.h"
#include "RootNode.h"

namespace dpm
{
	struct PlayerSlot
	{
		Player *const player;
		Cash cash;

		explicit PlayerSlot(Player *player);
	};

	class KuhnPoker
	{
	public:
		KuhnPoker(Player *playerA, Player *playerB);

		void play(Cash startCapital, int maxIterations = 100);

		void trainPlayer(unsigned int iterations, PlayerIndex playerIndex, bool playAgainstOtherPlayer);

	private:
		const RootNode m_GameTree;

		std::array<PlayerSlot, PlayerIndices::getNumberOfPlayers()> m_PlayerSlots;
		std::array<PlayerSlot *, PlayerIndices::getNumberOfPlayers()> m_PlayerOrder;

		Cash m_BuyIn;

		std::default_random_engine m_Rng;

	private:
		[[nodiscard]] Hands drawHands();

		void switchPlayerIndices();

		void resetPlayerIndices();

		[[nodiscard]] PlayerSlot *getWinner();
	};
}

#endif //KUHN_POKER_KUHNPOKER_H
