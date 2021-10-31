#ifndef KUHN_POKER_ROOTNODE_H
#define KUHN_POKER_ROOTNODE_H

#include "History.h"
#include "Tree/InternalNode.h"
#include "Tree/NodeBase.h"

namespace dpm
{

	template<GameMode TGameMode>
	class RootNode
	{
		using Hands = std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()>;

	public:
		RootNode();

		void generateChildren(RuleSet<TGameMode> *ruleSet);

	private:
		[[nodiscard]] static bool
		handsContainCard(const std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()> &hands,
		                 const Card &card);

	private:
		std::unordered_map<std::string, InternalNode<TGameMode> *> m_HandsToChildrenMapping;

	};

	template<GameMode TGameMode>
	RootNode<TGameMode>::RootNode()
			: m_HandsToChildrenMapping()
	{
	}

	template<GameMode TGameMode>
	bool RootNode<TGameMode>::handsContainCard(
			const std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()> &hands,
			const Card &card)
	{
		for (const auto &playerHand: hands)
			if (playerHand.containsCard(card))
				return true;
		return false;
	}

	template<GameMode TGameMode>
	void RootNode<TGameMode>::generateChildren(RuleSet<TGameMode> *ruleSet)
	{
		constexpr auto allCards = RuleSet<TGameMode>::getAllCards();
		constexpr auto numberOfCards = allCards.size();
		constexpr auto numberOfCardsPerPlayer = RuleSet<TGameMode>::getNumberOfCardsPerPlayer();
		constexpr auto numberOfPlayers = RuleSet<TGameMode>::getNumberOfPlayers();

		std::vector<typename State<TGameMode>::PlayerCards> hands;

		for (auto playerIndex = 0; playerIndex < numberOfPlayers; ++playerIndex)
		{
			for (auto cardIndex = 0; cardIndex < numberOfCardsPerPlayer; ++cardIndex)
			{
				if (hands.empty())
				{
					for (const auto &card: allCards)
						hands.push_back({Hand<TGameMode>{card}, Hand<TGameMode>{}});
				}
				else
				{
					const auto handsSize = hands.size();
					for (auto handIndex = 0u; handIndex < hands.size(); ++handIndex)
					{
						auto &playerHands = hands.at(handIndex);
						auto addedCard = false;
						for (const auto &card: allCards)
						{
							if (handsContainCard(playerHands, card))
								continue;
							if (addedCard)
							{
								auto newPlayerHands = playerHands;
								newPlayerHands.at(playerIndex).setCard(cardIndex, card);
								hands.push_back(newPlayerHands);
							}
							else
							{
								playerHands.at(playerIndex).addCard(card);
								addedCard = true;
							}
						}
					}
				}
			}
		}
		for (auto &playerHands: hands)
		{
			std::stringstream ss;
			for (const auto &hand: playerHands)
				ss << hand;
			History<TGameMode> history(std::move(playerHands), ruleSet->getSmallBlind(), ruleSet->getBigBlind());
			auto child = InternalNode<TGameMode>::createInternalNode(history.getFinalState());
			const auto turnOptions = history.getPossibleMoves();
			child->generateChildren(turnOptions, history);
			m_HandsToChildrenMapping.emplace(ss.str(), child);
		}
		int i = 1;
	}
}

#endif //KUHN_POKER_ROOTNODE_H
