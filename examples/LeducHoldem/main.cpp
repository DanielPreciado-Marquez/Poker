#include "DPMpoker/DPMpoker.hpp"

int main()
{
	dpm::Player playerA;
	dpm::Player playerB;
	dpm::Poker<dpm::GameMode::LeducHoldem> poker;
	poker.setPlayers({&playerA, &playerB});
	// 288 information sets
	poker.trainPlayer(1000, 0, false);
	return 0;
}
