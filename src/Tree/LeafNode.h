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

	private:
		static std::vector<std::unique_ptr<LeafNode>> s_Nodes;

	};

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
}

#endif //POKER_LEAFNODE_H
