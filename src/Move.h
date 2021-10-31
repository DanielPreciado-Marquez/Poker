#ifndef POKER_MOVE_H
#define POKER_MOVE_H

#include "Enums/MoveType.h"

namespace dpm
{
	struct Move
	{
		constexpr Move() = default;

		virtual ~Move();

		[[nodiscard]] virtual MoveType getMoveType() const = 0;
	};
}



#endif //POKER_MOVE_H
