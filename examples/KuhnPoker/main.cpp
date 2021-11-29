#include "DPMpoker/DPMpoker.hpp"

int main()
{
	dpm::Player playerA;
	dpm::Player playerB;
	dpm::Poker<dpm::GameMode::KuhnPoker> poker;
	poker.setPlayers({&playerA, &playerB});
	poker.trainPlayer(100000, 0, false);
	return 0;
}
