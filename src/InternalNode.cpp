#include "InternalNode.h"

#include "LeafNode.h"
#include "Player.h"

namespace dpm
{
	InternalNode::InternalNode(State &&state)
			: NodeBase(std::move(state))
	{
		generateChildren();
	}

	void InternalNode::generateChildren()
	{
		switch (m_State.turn)
		{
			case Turns::Turn1:
			{
				switch (m_State.nextPlayer)
				{
					case PlayerIndices::Player1:
						// Player1 can bet and check
						m_Children.at(Moves::Bet) = std::make_shared<InternalNode>(State(m_State.cards,
						                                                                 PlayerIndices::Player2,
						                                                                 Turns::Turn1,
						                                                                 Stakes::StakeBet,
						                                                                 Stakes::StakeBegin));
						m_Children.at(Moves::Check) = std::make_shared<InternalNode>(State(m_State.cards,
						                                                                   PlayerIndices::Player2,
						                                                                   Turns::Turn1,
						                                                                   Stakes::StakeChecked,
						                                                                   Stakes::StakeBegin));
						break;
					case PlayerIndices::Player2:
						if (m_State.stakes.at(PlayerIndices::Player1) == Stakes::StakeBet)
						{
							// Player1 bet, Player2 can call or fold
							m_Children.at(Moves::Call) = std::make_shared<LeafNode>(State(m_State.cards,
							                                                              PlayerIndices::NoPlayer,
							                                                              Turns::End,
							                                                              Stakes::StakeBet,
							                                                              Stakes::StakeCalled));
							m_Children.at(Moves::Fold) = std::make_shared<LeafNode>(State(m_State.cards,
							                                                              PlayerIndices::NoPlayer,
							                                                              Turns::End,
							                                                              Stakes::StakeBet,
							                                                              Stakes::StakeFolded));
						}
						else
						{
							// Player1 checked, Player2 can bet and check
							m_Children.at(Moves::Bet) = std::make_shared<InternalNode>(State(m_State.cards,
							                                                                 PlayerIndices::Player1,
							                                                                 Turns::Turn2,
							                                                                 Stakes::StakeChecked,
							                                                                 Stakes::StakeBet));
							m_Children.at(Moves::Check) = std::make_shared<LeafNode>(State(m_State.cards,
							                                                               PlayerIndices::NoPlayer,
							                                                               Turns::End,
							                                                               Stakes::StakeChecked,
							                                                               Stakes::StakeChecked));
						}
						break;
				}
				break;
			}
			case Turns::Turn2:
			{
				// Player1 checked, Player2 bet, Player1 can call or fold
				m_Children.at(Moves::Call) = std::make_shared<LeafNode>(State(m_State.cards,
				                                                              PlayerIndices::NoPlayer,
				                                                              Turns::End,
				                                                              Stakes::StakeCalled,
				                                                              Stakes::StakeBet));
				m_Children.at(Moves::Fold) = std::make_shared<LeafNode>(State(m_State.cards,
				                                                              PlayerIndices::NoPlayer,
				                                                              Turns::End,
				                                                              Stakes::StakeFolded,
				                                                              Stakes::StakeBet));
			}
		}
	}

	Outcome InternalNode::getOutcome(const History &history) const
	{
		return m_Children.at(history.at(getHistoryIndex()))->getOutcome(history);
	}

	float InternalNode::cfr(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
	                        const PlayerIndex playerIndex,
	                        const Hands &hands,
	                        const History &history,
	                        const ReachProbabilities reachProbabilities,
	                        const int playerIndexToUpdate) const
	{
		const auto playerCard = hands.at(playerIndex);
		auto &informationSet = players.at(playerIndex)->getInformationSet(playerCard, history);
		const auto strategy = informationSet.updateStrategy(reachProbabilities.at(playerIndex));
		const auto nextPlayerIndex = static_cast<PlayerIndex>((playerIndex + 1) % PlayerIndices::getNumberOfPlayers());
		std::array<float, Moves::getNumberOfMoves()> counterfactualValues{0.0f, 0.0f};
		for (const auto move: Moves::getAllMoves())
		{
			auto updatedHistory = history;
			updatedHistory.at(getHistoryIndex()) = move;
			auto nextReachProbabilities = reachProbabilities;
			nextReachProbabilities.at(playerIndex) *= strategy.at(move);
			counterfactualValues.at(move) = -m_Children.at(move)->cfr(players,
			                                                          nextPlayerIndex,
			                                                          hands,
			                                                          updatedHistory,
			                                                          nextReachProbabilities,
			                                                          playerIndexToUpdate);
		}
		auto nodeValue = 0.0f;
		for(auto i = 0u; i < Moves::getNumberOfMoves(); ++i)
			nodeValue += counterfactualValues.at(i) * strategy.at(i);
		for (const auto move: Moves::getAllMoves())
			informationSet.updateCumulativeRegret(move, reachProbabilities.at(nextPlayerIndex) * (counterfactualValues.at(move) - nodeValue));
		return nodeValue;
	}

	float InternalNode::cfr2(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
	                         const PlayerIndex playerIndex,
	                         const Hands &hands,
	                         const History &history,
	                         const ReachProbabilities reachProbabilities,
	                         const int playerIndexToUpdate) const
	{
		const auto playerCard = hands.at(playerIndex);
		auto &informationSet = players.at(playerIndex)->getInformationSet(playerCard, history);
		const auto &strategy = informationSet.getStrategy();
		const auto nextPlayerIndex = static_cast<PlayerIndex>((playerIndex + 1) % PlayerIndices::getNumberOfPlayers());
		std::array<float, Moves::getNumberOfMoves()> counterfactualValues{0.0f, 0.0f};
		auto counterfactualSum = 0.0f;
		for (const auto move: Moves::getAllMoves())
		{
			auto updatedHistory = history;
			updatedHistory.at(getHistoryIndex()) = move;
			auto nextReachProbabilities = reachProbabilities;
			nextReachProbabilities.at(playerIndex) *= strategy.at(move);
			const float counterfactualValue = -m_Children.at(move)->cfr(players,
			                                                            nextPlayerIndex,
			                                                            hands,
			                                                            updatedHistory,
			                                                            nextReachProbabilities,
			                                                            playerIndexToUpdate);
			counterfactualSum += strategy.at(move) * counterfactualValue;
			counterfactualValues.at(move) = counterfactualValue;
		}
		for (const auto move: Moves::getAllMoves())
		{

			const auto regret = counterfactualValues.at(move) - counterfactualSum;
			const auto posRegret = std::max(0.0f, regret);
			if (playerIndexToUpdate == -1 || playerIndexToUpdate == playerIndex)
				informationSet.updateCumulativeRegret(move, posRegret);
		}
		informationSet.normalizeStrategy();
		return counterfactualSum;
	}
}
