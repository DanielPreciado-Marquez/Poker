#include "KuhnPoker.h"

namespace dpm
{
	PlayerSlot::PlayerSlot(Player *const player)
			: player(player)
			, cash(0)
	{
	}

	KuhnPoker::KuhnPoker(Player *const playerA, Player *const playerB)
			: m_GameTree()
			, m_PlayerSlots({PlayerSlot{playerA}, PlayerSlot{playerB}})
			, m_PlayerOrder({&m_PlayerSlots.at(0), &m_PlayerSlots.at(1)})
			, m_BuyIn(1)
			, m_Rng(std::random_device()())
	{
	}

	void KuhnPoker::play(const Cash startCapital, const int maxIterations)
	{
		for (auto &playerSlot: m_PlayerSlots)
			playerSlot.cash = startCapital;

		auto i = 0;
		PlayerSlot *winner = nullptr;
		while (i != maxIterations && !winner)
		{
			const auto hands = drawHands();
			for (auto &playerSlot: m_PlayerSlots)
				playerSlot.cash -= m_BuyIn;

			History history{Moves::NoMove, Moves::NoMove, Moves::NoMove};

			history.at(0) = m_PlayerOrder.at(PlayerIndices::Player1)->player->getNextMove(hands.at(PlayerIndices::Player1),
			                                                                              history);
			if (history.at(0) == Moves::Bet)
				m_PlayerOrder.at(PlayerIndices::Player1)->cash -= 1;

			history.at(1) = m_PlayerOrder.at(PlayerIndices::Player2)->player->getNextMove(hands.at(PlayerIndices::Player2),
			                                                                              history);
			if (history.at(1) == Moves::Bet || history.at(1) == Moves::Call)
				m_PlayerOrder.at(PlayerIndices::Player2)->cash -= 1;

			if (history.at(0) == Moves::Check && history.at(1) == Moves::Bet)
			{
				history.at(2) = m_PlayerOrder.at(PlayerIndices::Player1)->player->getNextMove(hands.at(PlayerIndices::Player1),
				                                                                              history);
				if (history.at(2) == Moves::Call)
					m_PlayerOrder.at(PlayerIndices::Player1)->cash -= 1;
			}
			const auto outcome = m_GameTree.getOutcome(hands, history);

			m_PlayerOrder.at(outcome.winner)->cash += outcome.stake;
			winner = getWinner();
			++i;
			switchPlayerIndices();
		}
		resetPlayerIndices();
		std::cout << i << std::endl;
	}

	void KuhnPoker::trainPlayer(const unsigned int iterations,
	                            PlayerIndex playerIndex,
	                            const bool playAgainstOtherPlayer)
	{
		std::array<Player *, PlayerIndices::getNumberOfPlayers()> player{m_PlayerSlots.at(0).player,
		                                                                 m_PlayerSlots.at(0).player};
		if (playAgainstOtherPlayer)
			player.at(1) = m_PlayerSlots.at(1).player;
		else
			playerIndex = -1;

		auto regret = 0.0f;
		for (auto i = 0u; i < iterations; ++i)
		{
			const auto hands = drawHands();
			regret += m_GameTree.trainPlayer(player,
			                                 PlayerIndices::Player1,
			                                 hands,
			                                 History{-1, -1, -1},
			                                 ReachProbabilities{1.0f, 1.0f},
			                                 playerIndex);
			if (playAgainstOtherPlayer)
				std::rotate(player.begin(), player.begin() + 1, player.end());
		}
		const auto average = regret / iterations;
		resetPlayerIndices();
	}

	Hands KuhnPoker::drawHands()
	{
		auto deck = Cards::getAllCards();
		std::shuffle(deck.begin(), deck.end(), m_Rng);
		return {deck.at(PlayerIndices::Player1), deck.at(PlayerIndices::Player2)};
	}

	void KuhnPoker::switchPlayerIndices()
	{
		std::rotate(m_PlayerOrder.begin(), m_PlayerOrder.begin() + 1, m_PlayerOrder.end());
	}

	void KuhnPoker::resetPlayerIndices()
	{
		for (auto i = 0u; i < PlayerIndices::getNumberOfPlayers(); ++i)
			m_PlayerOrder.at(i) = &m_PlayerSlots.at(i);
	}

	PlayerSlot *KuhnPoker::getWinner()
	{
		PlayerSlot *winner = nullptr;
		for (auto &playerSlot: m_PlayerSlots)
		{
			if (playerSlot.cash > 0)
			{
				if (winner)
					return nullptr;
				else
					winner = &playerSlot;
			}
		}
		return winner;
	}

}
