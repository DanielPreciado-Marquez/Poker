#ifndef POKER_INTERNALNODE_H
#define POKER_INTERNALNODE_H

#include "Enums/GameMode.h"
#include "RuleSet/RuleSet.h"
#include "Tree/DecisionNode.h"
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

		float cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
		          PlayerIndex playerIndex,
		          History<TGameMode> &history,
		          std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
		          int playerIndexToUpdate) const override;

	private:
		static std::vector<std::unique_ptr<InternalNode>> s_Nodes;

	private:
		std::array<NodeBase<TGameMode> *, NUMBER_OF_PLAYER_ACTIONS> m_Children;
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
		for (auto i = 0u; i < NUMBER_OF_PLAYER_ACTIONS; ++i)
		{
			const auto &playerMove = turnOptions.possiblePlayerMoves.at(i);
			if (playerMove.playerAction == PlayerAction::NoAction)
				continue;
			const auto currentRoundIndex = history.getCurrentRoundIndex();
			const auto nextMoveIndex = history.getNextMoveIndex();
			history.applyMove(playerMove, turnOptions.nextPlayer);
			auto childState = history.getFinalState();
			const auto nextTurnOptions = history.getPossibleMoves();
			if (nextTurnOptions.nextPlayer == PlayerIndices::Dealer)
			{
				auto child = ChanceNode<TGameMode>::createChanceNode(std::move(childState));
				m_Children.at(i) = child;
				child->generateChildren(nextTurnOptions, history);
			}
			else if (nextTurnOptions.nextPlayer == PlayerIndices::NoPlayer)
			{
				m_Children.at(i) = LeafNode<TGameMode>::createLeafNode(std::move(childState));
			}
			else
			{
				auto child = InternalNode<TGameMode>::createInternalNode(std::move(childState));
				m_Children.at(i) = child;
				child->generateChildren(nextTurnOptions, history);
			}
			history.rollback(this->m_State, currentRoundIndex, nextMoveIndex);
		}
	}

	template<GameMode TGameMode>
	float InternalNode<TGameMode>::cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
	                                   PlayerIndex playerIndex,
	                                   History<TGameMode> &history,
	                                   std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
	                                   int playerIndexToUpdate) const
	{
		const auto turnOptions = history.getPossibleMoves();

		const auto &playerHand = this->m_State.playerHands.at(playerIndex);
		auto &informationSet = players.at(playerIndex)->getInformationSet<TGameMode>(playerIndex, history, turnOptions);
		const auto strategy = informationSet.updateStrategy(reachProbabilities.at(playerIndex));

		std::vector<float> counterfactualValues(m_Children.size());
		auto counterfactualSum = 0.0f;

		// TODO more players
		const auto nextPlayerIndex = (turnOptions.nextPlayer + 1) % 2;

		for (auto i = 0u; i < NUMBER_OF_PLAYER_ACTIONS; ++i)
		{
			const auto &playerMove = turnOptions.possiblePlayerMoves.at(i);
			if (playerMove.playerAction == PlayerAction::NoAction)
				continue;
			const auto currentRoundIndex = history.getCurrentRoundIndex();
			const auto nextMoveIndex = history.getNextMoveIndex();
			history.applyMove(playerMove, turnOptions.nextPlayer);
			auto nextReachProbabilities = reachProbabilities;
			nextReachProbabilities.at(playerIndex) *= strategy.at(i);
			const float counterfactualValue = -m_Children.at(i)->cfr(players,
			                                                         nextPlayerIndex,
			                                                         history,
			                                                         nextReachProbabilities,
			                                                         playerIndexToUpdate);
			counterfactualSum += strategy.at(i) * counterfactualValue;
			counterfactualValues.at(i) = counterfactualValue;
			history.rollback(this->m_State, currentRoundIndex, nextMoveIndex);
		}
		if (playerIndexToUpdate == -1 || playerIndexToUpdate == playerIndex)
		{
			for (auto i = 0u; i < NUMBER_OF_PLAYER_ACTIONS; ++i)
			{
				const auto &playerMove = turnOptions.possiblePlayerMoves.at(i);
				if (playerMove.playerAction == PlayerAction::NoAction)
					continue;
				informationSet.updateCumulativeRegret(i,
				                                      reachProbabilities.at(nextPlayerIndex) *
				                                      (counterfactualValues.at(i) - counterfactualSum));
			}
		}
		return counterfactualSum;
	}
}

#endif //POKER_INTERNALNODE_H
