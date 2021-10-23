#include "KuhnPoker.h"

int main()
{
	dpm::Player playerA;
	dpm::Player playerB;
	dpm::KuhnPoker game(&playerA, &playerB);
	//game.play(10);
	game.trainPlayer(100000, dpm::PlayerIndices::Player1, false);
	return 0;
}
