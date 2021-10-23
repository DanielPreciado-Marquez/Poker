#include "enums.h"

namespace dpm
{
	std::string PlayerIndices::toString(const PlayerIndex playerIndex)
	{
		switch (playerIndex)
		{
			case NoPlayer:
				return "NoPlayer";
			case Player1:
				return "Player1";
			case Player2:
				return "Player2";
			default:
				return "Unknown";
		}
	}

	std::string Cards::toString(Card card)
	{
		switch (card)
		{
			case NoCard:
				return "NoCard";
			case Jack:
				return "Jack";
			case Queen:
				return "Queen";
			case King:
				return "King";
			default:
				return "Unknown";
		}
	}

	std::string historyToString(const History &history)
	{
		std::stringstream ss;

		ss << "Move 1: ";
		if (history.at(0) == Moves::Bet)
			ss << "Bet";
		else if (history.at(0) == Moves::Check)
			ss << "Check";
		else
			ss << "NoMove";

		ss << ", Move 2: ";
		if (history.at(0) == Moves::Bet)
		{
			if (history.at(1) == Moves::Fold)
				ss << "Fold";
			else if (history.at(1) == Moves::Call)
				ss << "Call";
			else
				ss << "NoMove";
		}
		else if (history.at(0) == Moves::Check)
		{
			if (history.at(1) == Moves::Bet)
				ss << "Bet";
			else if (history.at(1) == Moves::Check)
				ss << "Check";
			else
				ss << "NoMove";
		}

		ss << ", Move 3: ";
		if (history.at(2) == Moves::Fold)
			ss << "Fold";
		else if (history.at(2) == Moves::Call)
			ss << "Call";
		else
			ss << "NoMove";

		return ss.str();
	}
}
