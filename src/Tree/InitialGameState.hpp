#ifndef POKER_INITIALGAMESTATE_HPP
#define POKER_INITIALGAMESTATE_HPP

#include "Tree/GameState.hpp"

namespace dpm
{
	template<GameMode TGameMode>
	class InitialGameState : public State<TGameMode>
	{
	public:
		explicit InitialGameState(State<TGameMode> &&initialState);

		[[nodiscard]]
		bool isTerminal() const override;

		void generateChildren();

		const GameState<TGameMode> *getGameState(const typename State<TGameMode>::PlayerHands &playerHands) const;

	private:
		[[nodiscard]] static bool handsContainCard(const typename State<TGameMode>::PlayerHands &hands,
		                                           const Card &card);

	private:
		std::array<GameState<TGameMode> *, RuleSet<TGameMode>::NUMBER_OF_HAND_COMBINATIONS> m_Children;
	};

	template<GameMode TGameMode>
	InitialGameState<TGameMode>::InitialGameState(State<TGameMode> &&initialState)
			: State<TGameMode>(std::move(initialState))
			, m_Children()
	{
	}

	template<GameMode TGameMode>
	bool InitialGameState<TGameMode>::isTerminal() const
	{
		return false;
	}

	template<GameMode TGameMode>
	void InitialGameState<TGameMode>::generateChildren()
	{
		constexpr auto allCards = RuleSet<TGameMode>::ALL_CARDS;
		constexpr auto numberOfCards = allCards.size();
		constexpr auto numberOfCardsPerPlayer = RuleSet<TGameMode>::NUMBER_OF_CARDS_PER_PLAYER;
		constexpr auto numberOfPlayers = RuleSet<TGameMode>::NUMBER_OF_PLAYERS;

		std::vector<typename State<TGameMode>::PlayerHands> hands;

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
		for (auto i = 0u; i < hands.size(); ++i)
		{
			auto child = GameState<TGameMode>::createGameState(State<TGameMode>(*this));
			child->playerHands = std::move(hands.at(i));
			child->previousPlayer = PlayerIndices::Dealer;
			const auto turnOptions = child->getTurnOptions();
			child->generateChildren(turnOptions);
			m_Children.at(i) = child;
		}
	}

	template<GameMode TGameMode>
	const GameState<TGameMode> *
	InitialGameState<TGameMode>::getGameState(const typename State<TGameMode>::PlayerHands &playerHands) const
	{
		for (const auto state: m_Children)
			if (state->playerHandsEqual(playerHands))
				return state;
		return nullptr;
	}

	template<GameMode TGameMode>
	bool InitialGameState<TGameMode>::handsContainCard(const typename State<TGameMode>::PlayerHands &hands,
	                                                   const Card &card)
	{
		for (const auto &playerHand: hands)
			if (playerHand.containsCard(card))
				return true;
		return false;
	}

}

#endif //POKER_INITIALGAMESTATE_HPP
