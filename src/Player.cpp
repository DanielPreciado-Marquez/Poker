#include "Player.h"

namespace dpm
{
	Player::Player()
		: m_Strategies()
		, m_Rng(std::random_device()())
		, m_Distribution(0.0f, 1.0f)
	{
	}

}
