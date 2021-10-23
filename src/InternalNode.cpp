#include "InternalNode.h"

#include "LeafNode.h"

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
		return m_Children.at(history.at(PlayerIndices::getNumberOfPlayers() * m_State.turn + m_State.nextPlayer))->getOutcome(history);
	}
}
