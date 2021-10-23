#include "RootNode.h"

namespace dpm
{
	RootNode::RootNode()
			: m_Trees()
	{
		generateTrees();
	}

	Outcome RootNode::getOutcome(const Hands &hands, const History &history) const
	{
		return getTreeFromHands(hands)->getOutcome(history);
	}

	void RootNode::generateTrees()
	{
		for (const auto cardPlayer1: Cards::getAllCards())
			for (const auto cardPlayer2: Cards::getAllCards())
				if (cardPlayer1 != cardPlayer2)
					m_Trees.at(cardPlayer1).at(cardPlayer2) = std::make_shared<InternalNode>(State({cardPlayer1,
					                                                                                cardPlayer2},
					                                                                               PlayerIndices::Player1,
					                                                                               Turns::Turn1,
					                                                                               Stakes::StakeBegin,
					                                                                               Stakes::StakeBegin));
	}

	float RootNode::trainPlayer(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
	                            PlayerIndex playerIndex, const Hands &hands, const History &history,
	                            ReachProbabilities reachProbabilities, int playerIndexToUpdate) const
	{
		return getTreeFromHands(hands)->cfr(players,
		                                    playerIndex,
		                                    hands,
		                                    history,
		                                    reachProbabilities,
		                                    playerIndexToUpdate);
	}

	InternalNode *RootNode::getTreeFromHands(const Hands &hands) const
	{
		return m_Trees.at(hands.at(PlayerIndices::Player1)).at(hands.at(PlayerIndices::Player2)).get();
	}
}
