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

		float cfr(const std::array<Player *, RuleSet<TGameMode>::getNumberOfPlayers()> &players,
		          PlayerIndex playerIndex,
		          History<TGameMode> &history,
		          std::array<float, RuleSet<TGameMode>::getNumberOfPlayers()> reachProbabilities,
		          int playerIndexToUpdate) const override;

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

	template<GameMode TGameMode>
	float InternalNode<TGameMode>::cfr(const std::array<Player *, RuleSet<TGameMode>::getNumberOfPlayers()> &players,
	                                   PlayerIndex playerIndex,
	                                   History<TGameMode> &history,
	                                   std::array<float, RuleSet<TGameMode>::getNumberOfPlayers()> reachProbabilities,
	                                   int playerIndexToUpdate) const
	{
		const auto &playerHand = this->m_State.playerCards.at(playerIndex);
		auto &informationSet = players.at(playerIndex)->getInformationSet<TGameMode>(playerIndex, history);
		const auto strategy = informationSet.updateStrategy(reachProbabilities.at(playerIndex));

		std::vector<float> counterfactualValues(m_Children.size());
		auto counterfactualSum = 0.0f;

		const auto turnOptions = history.getPossibleMoves();
		// TODO more players
		const auto nextPlayerIndex = (turnOptions.nextPlayer + 1) % 2;

		auto moveIndex = 0u;
		for (const auto playerMove: turnOptions.possiblePlayerMoves)
		{
			if (playerMove.playerAction == PlayerAction::NoAction)
				continue;
			const auto currentRoundIndex = history.getCurrentRoundIndex();
			const auto nextMoveIndex = history.getNextMoveIndex();
			history.applyMove(playerMove, turnOptions.nextPlayer);
			auto nextReachProbabilities = reachProbabilities;
			nextReachProbabilities.at(playerIndex) *= strategy.at(moveIndex);
			const float counterfactualValue = -m_Children.at(moveIndex)->cfr(players,
			                                                                 nextPlayerIndex,
			                                                                 history,
			                                                                 nextReachProbabilities,
			                                                                 playerIndexToUpdate);
			counterfactualSum += strategy.at(moveIndex) * counterfactualValue;
			counterfactualValues.at(moveIndex) = counterfactualValue;
			history.rollback(this->m_State, currentRoundIndex, nextMoveIndex);
			++moveIndex;
		}
		moveIndex = 0;
		if (playerIndexToUpdate == -1 || playerIndexToUpdate == playerIndex)
		{
			for (const auto playerMove: turnOptions.possiblePlayerMoves)
			{
				if (playerMove.playerAction == PlayerAction::NoAction)
					continue;
				informationSet.updateCumulativeRegret(moveIndex,
				                                      reachProbabilities.at(nextPlayerIndex) *
				                                      (counterfactualValues.at(moveIndex) - counterfactualSum));
				++moveIndex;
			}
		}
		return counterfactualSum;
	}
}

#endif //POKER_INTERNALNODE_H
