#ifndef KUHN_POKER_MOVE_H
#define KUHN_POKER_MOVE_H

#include "enums.h"

namespace dpm
{
	enum class MoveName
	{
		NoMove,

		Bet,
		Check,

		Call,
		Fold
	};

	using MoveIndex = int8_t;

	template<MoveName TMoveName>
	class Move
	{
	public:
		[[nodiscard]] constexpr std::size_t getNumberOfMoves()
		{
			return 2;
		}

		[[nodiscard]] static constexpr MoveName getMoveName()
		{
			return TMoveName;
		}

		[[nodiscard]] static constexpr MoveIndex getIndex()
		{
			if constexpr(TMoveName == MoveName::Bet || TMoveName == MoveName::Call)
				return 0;
			else if constexpr(TMoveName == MoveName::Check || TMoveName == MoveName::Fold)
				return 1;
			else
				return -1;
		}

		[[nodiscard]] static constexpr std::string_view toStringView()
		{
			if constexpr(TMoveName == MoveName::NoMove)
				return "Bet";
			else if constexpr(TMoveName == MoveName::Bet)
				return "Bet";
			else if constexpr(TMoveName == MoveName::Check)
				return "Check";
			else if constexpr(TMoveName == MoveName::Call)
				return "Call";
			else if constexpr(TMoveName == MoveName::Fold)
				return "Fold";
			else
				return "Unknown";
		}

		[[nodiscard]] static std::string toString()
		{
			return std::string(Move::toStringView());
		}
	};

	using History = std::array<MoveName, getNumberOfTurns()>;

	std::ostream &operator<<(std::ostream &ostream, MoveName moveName)
	{
		return ostream << Move<>::toStringView();
	}

}

#endif //KUHN_POKER_MOVE_H
