#ifndef POKER_INTERNALNODE_H
#define POKER_INTERNALNODE_H

#include "Enums/GameMode.h"
#include "RuleSet/RuleSet.h"
#include "Tree/LeafNode.h"
#include "Tree/NodeBase.h"

namespace dpm
{
	template<GameMode TGameMode>
	class InternalNode : NodeBase<TGameMode>
	{
	public:
		static InternalNode *createInternalNode(State<TGameMode> state);

	public:

		InternalNode();

		explicit InternalNode(State<TGameMode> &&state);

		void generateChildren(const TurnOptions<TGameMode> &turnOptions, History<TGameMode> &history) override;

	private:
		static std::vector<std::unique_ptr<InternalNode>> s_Nodes;

	private:
		std::array<NodeBase<TGameMode> *, RuleSet<TGameMode>::getNumberOfPossibleActions()> m_Children;
	};

	template<GameMode TGameMode>
	std::vector<std::unique_ptr<InternalNode<TGameMode>>> InternalNode<TGameMode>::s_Nodes = {};

	template<GameMode TGameMode>
	InternalNode<TGameMode> *InternalNode<TGameMode>::createInternalNode(State<TGameMode> state)
	{
		s_Nodes.push_back(std::make_unique<InternalNode<TGameMode>>(std::move(state)));
		return s_Nodes.back().get();
	}

	template<GameMode TGameMode>
	InternalNode<TGameMode>::InternalNode()
			: NodeBase<TGameMode>()
			, m_Children()
	{
	}

	template<GameMode TGameMode>
	InternalNode<TGameMode>::InternalNode(State<TGameMode> &&state)
			: NodeBase<TGameMode>(std::move(state))
	{
	}

	template<GameMode TGameMode>
	void InternalNode<TGameMode>::generateChildren(const TurnOptions<TGameMode> &turnOptions,
	                                               History<TGameMode> &history)
	{
		auto index = 0;
		for (const auto &playerMove: turnOptions.possiblePlayerMoves)
		{
			if (playerMove.playerAction == PlayerAction::NoAction)
				continue;
			const auto currentRoundIndex = history.getCurrentRoundIndex();
			const auto nextMoveIndex = history.getNextMoveIndex();
			history.applyMove(playerMove, turnOptions.nextPlayer);
			auto childState = history.getFinalState();
			const auto nextTurnOptions = history.getPossibleMoves();
			if (nextTurnOptions.nextPlayer == PlayerIndices::Dealer)
			{
				// TODO
			}
			else if (nextTurnOptions.nextPlayer == PlayerIndices::NoPlayer)
			{
				auto child = LeafNode<TGameMode>::createLeafNode(std::move(childState));
				m_Children.at(index) = child;
			}
			else
			{
				auto child = InternalNode<TGameMode>::createInternalNode(std::move(childState));
				m_Children.at(index) = child;
				child->generateChildren(nextTurnOptions, history);
			}
			history.rollback(this->m_State, currentRoundIndex, nextMoveIndex);
			++index;
		}
	}
}

#endif //POKER_INTERNALNODE_H
