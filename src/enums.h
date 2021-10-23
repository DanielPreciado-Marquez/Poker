#ifndef KUHN_POKER_ENUMS_H
#define KUHN_POKER_ENUMS_H

namespace dpm
{
	using Cash = unsigned int;
	using Stake = std::uint8_t;

	namespace Stakes
	{
		enum : Stake
		{
			StakeBegin = 1,
			StakeBet = 2,
			StakeChecked = StakeBegin,
			StakeFolded = StakeBegin,
			StakeCalled = StakeBet
		};
	}

	using Turn = std::uint8_t;

	namespace Turns
	{
		enum : Turn
		{
			Turn1 = 0,
			Turn2 = 1,
			End = 2
		};
	}

	constexpr std::size_t getNumberOfTurns()
	{
		return 3;
	}

	// --- PlayerIndices ---

	using PlayerIndex = std::int8_t;

	namespace PlayerIndices
	{
		enum : PlayerIndex
		{
			NoPlayer = -1,
			Player1 = 0,
			Player2 = 1
		};

		std::string toString(PlayerIndex playerIndex);

		constexpr std::size_t getNumberOfPlayers()
		{
			return 2;
		}
	}

	// --- Cards ---

	using Card = std::int8_t;

	namespace Cards
	{
		enum : Card
		{
			NoCard = -1,
			Jack = 0,
			Queen = 1,
			King = 2
		};

		std::string toString(Card card);

		constexpr std::array<Card, 3> getAllCards()
		{
			return {Cards::Jack, Cards::Queen, Cards::King};
		}

		constexpr std::size_t getNumberOfCards()
		{
			return 3;
		}
	}

	// --- Moves ---

	using Move = int8_t;

	namespace Moves
	{
		enum : Move
		{
			NoMove = -1,

			Bet = 0,
			Check = 1,

			Call = 0,
			Fold = 1
		};

		constexpr std::size_t getNumberOfMoves()
		{
			return 2;
		}
	}

	using Hands = std::array<Card, PlayerIndices::getNumberOfPlayers()>;
	using History = std::array<Move, getNumberOfTurns()>;

	std::string historyToString(const History &history);
}

#endif //KUHN_POKER_ENUMS_H
