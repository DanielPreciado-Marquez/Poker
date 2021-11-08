#include "DealerAction.h"

namespace dpm
{
	std::string toString(DealerAction dealerAction)
	{
		switch (dealerAction)
		{
			case DealerAction::NoAction:
				return "NoAction";
			case DealerAction::DrawPlayerCards:
				return "DrawPlayerCards";
			case DealerAction::DrawCommunityCards:
				return "DrawCommunityCards";
			default:
				return "UnknownAction";
		}
	}
}
