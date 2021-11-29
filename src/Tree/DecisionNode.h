#ifndef POKER_CHANCENODE_H
#define POKER_CHANCENODE_H

#include "Tree/NodeBase.h"

namespace dpm
{
	template<GameMode TGameMode>
	class ChanceNode : public NodeBase<TGameMode>
	{
	public:
		static ChanceNode *createChanceNode(State<TGameMode> state);

	public:
		explicit ChanceNode(State<TGameMode> &&state);

		void generateChildren(const TurnOptions<TGameMode> &turnOptions, History<TGameMode> &history) override;

		float cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
		          PlayerIndex playerIndex,
		          History<TGameMode> &history,
		          std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
		          int playerIndexToUpdate) const override;

	private:
		static std::vector<std::unique_ptr<ChanceNode>> s_Nodes;

	};

	template<GameMode TGameMode>
	ChanceNode<TGameMode> *ChanceNode<TGameMode>::createChanceNode(State<TGameMode> state)
	{
		s_Nodes.push_back(std::make_unique<ChanceNode<TGameMode>>(std::move(state)));
		return s_Nodes.back().get();
	}

	template<GameMode TGameMode>
	ChanceNode<TGameMode>::ChanceNode(State<TGameMode> &&state)
			: NodeBase<TGameMode>(std::move(state))
	{
	}

	template<GameMode TGameMode>
	void ChanceNode<TGameMode>::generateChildren(const TurnOptions<TGameMode> &turnOptions, History<TGameMode> &history)
	{

	}

	template<GameMode TGameMode>
	float ChanceNode<TGameMode>::cfr(const std::array<Player *, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> &players,
	                                 const PlayerIndex playerIndex,
	                                 History<TGameMode> &history,
	                                 std::array<float, RuleSet<TGameMode>::NUMBER_OF_PLAYERS> reachProbabilities,
	                                 const int playerIndexToUpdate) const
	{
		return 0;
	}
}

#endif //POKER_CHANCENODE_H
