#include "KuhnPoker.h"

int main()
{
	dpm::Player playerA;
	dpm::Player playerB;
	dpm::KuhnPoker game(&playerA, &playerB);
	game.play(10);
	return 0;
}
