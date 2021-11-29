#ifndef POKER_LEAFNODE_H
#define POKER_LEAFNODE_H

#include "Enums/GameMode.h"
#include "RuleSet/RuleSet.h"
#include "Tree/NodeBase.h"

namespace dpm
{
	template<GameMode TGameMode>
	class LeafNode : public NodeBase<TGameMode>
	{
	public:
		static LeafNode *createLeafNode(State<TGameMode> &&state);

	public:
		explicit LeafNode(State<TGameMode> &&state);

		void generateChildren(const TurnOptions<TGameMode> &turnOptions, History<TGameMode> &history) override;

		[[nodiscard]] Outcome getOutcome() const;

		float cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
		          PlayerIndex playerIndex,
		          History<TGameMode> &history,
		          std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
		          int playerIndexToUpdate) const override;

	private:
		static std::vector<std::unique_ptr<LeafNode>> s_Nodes;

	};

	// --- Implementation ---

	template<GameMode TGameMode>
	std::vector<std::unique_ptr<LeafNode<TGameMode>>> LeafNode<TGameMode>::s_Nodes = {};

	template<GameMode TGameMode>
	LeafNode<TGameMode> *LeafNode<TGameMode>::createLeafNode(State<TGameMode> &&state)
	{
		s_Nodes.push_back(std::make_unique<LeafNode<TGameMode>>(std::move(state)));
		return s_Nodes.back().get();
	}

	template<GameMode TGameMode>
	void LeafNode<TGameMode>::generateChildren(const TurnOptions<TGameMode> &turnOptions, History<TGameMode> &history)
	{
	}

	template<GameMode TGameMode>
	LeafNode<TGameMode>::LeafNode(State<TGameMode> &&state)
			: NodeBase<TGameMode>(std::move(state))
	{
	}

	template<GameMode TGameMode>
	Outcome LeafNode<TGameMode>::getOutcome() const
	{
		Cash pot = 0;
		for (const auto stake: this->m_State.stakes)
			pot += stake;

		PlayerIndex winner = PlayerIndices::NoPlayer;
		auto allButOneFolded = true;
		for (auto indexToCheck = 0u; indexToCheck < this->m_State.previousPlayerActions.size(); ++indexToCheck)
		{
			if (this->m_State.previousPlayerActions.at(indexToCheck) != PlayerAction::Fold)
			{
				if (winner == PlayerIndices::NoPlayer)
					winner = indexToCheck;
				else
					allButOneFolded = false;
			}
		}

		if (!allButOneFolded)
		{
			winner = 0;
			auto bestHand = this->m_State.playerHands.at(winner);
			for (auto indexToCheck = 1u; indexToCheck < this->m_State.playerHands.size(); ++indexToCheck)
			{
				const auto &handToCheck = this->m_State.playerHands.at(indexToCheck);
				if (bestHand < handToCheck)
				{
					winner = indexToCheck;
					bestHand = handToCheck;
				}
			}
		}

		return {winner, pot};
	}

	template<GameMode TGameMode>
	float LeafNode<TGameMode>::cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
	                               const PlayerIndex playerIndex,
	                               History<TGameMode> &history,
	                               std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
	                               const int playerIndexToUpdate) const
	{
		// TODO more than 2 players
		const auto outcome = getOutcome();
		const auto playerStake = this->m_State.stakes.at(playerIndex);
		if (outcome.winner == playerIndex)
			return float(outcome.stake - playerStake);
		else
			return -float(playerStake);
	}
}

#endif //POKER_LEAFNODE_H
