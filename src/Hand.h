#ifndef KUHN_POKER_HAND_H
#define KUHN_POKER_HAND_H

#include "Card.h"
#include "Enums/GameMode.h"
#include "RuleSet/RuleSet.h"

namespace dpm
{
	template<GameMode TGameMode>
	class Hand
	{
	public:
		std::array<Card, RuleSet<TGameMode>::getNumberOfCardsPerPlayer()> cards;

	public:
		Hand();

		Hand(std::initializer_list<Card> cards);

		[[nodiscard]] unsigned int size() const;

		[[nodiscard]] bool containsCard(const Card& card) const;

		void sort();

		void addCard(const Card &card);

		bool addCardIfNotPresent(const Card &card);

		void setCard(unsigned int cardIndex, const Card &card);

		[[nodiscard]] std::string toString() const;
	};

	template<GameMode TGameMode>
	std::ostream &operator<<(std::ostream &ostream, const Hand<TGameMode> &hand);

	// --- Implementation ---

	template<GameMode TGameMode>
	Hand<TGameMode>::Hand()
			: cards()
	{
	}

	template<GameMode TGameMode>
	Hand<TGameMode>::Hand(std::initializer_list<Card> cards)
	        : cards()
	{
		auto cardNumber = 0u;
		for(auto card : cards)
		{
			if (cardNumber >= this->cards.size())
				break;
			this->cards.at(cardNumber) = card;
			++cardNumber;
		}
		sort();
	}

	template<GameMode TGameMode>
	unsigned int Hand<TGameMode>::size() const
	{
		auto size = 0u;
		while (size < cards.size() && !cards.at(size).isEmpty())
			++size;
		return size;
	}

	template<GameMode TGameMode>
	bool Hand<TGameMode>::containsCard(const Card &card) const
	{
		const auto itr = std::find(cards.begin(), cards.end(), card);
		return itr != cards.end();
	}

	template<GameMode TGameMode>
	void Hand<TGameMode>::sort()
	{
		std::sort(cards.begin(), cards.begin() + size());
	}

	template<GameMode TGameMode>
	void Hand<TGameMode>::addCard(const Card &card)
	{
		auto cardItr = cards.begin();
		while (!cardItr->isEmpty())
		{
			++cardItr;
			if (cardItr == cards.end())
				return;
		}
		*cardItr = card;
		sort();
	}

	template<GameMode TGameMode>
	bool Hand<TGameMode>::addCardIfNotPresent(const Card &card)
	{
		auto cardItr = cards.begin();
		while (!cardItr->isEmpty())
		{
			if (*cardItr == card)
				return false;
			++cardItr;
			if (cardItr == cards.end())
				return false;
		}
		*cardItr = card;
		sort();
		return true;
	}

	template<GameMode TGameMode>
	void Hand<TGameMode>::setCard(unsigned int cardIndex, const Card &card)
	{
		cards.at(cardIndex) = card;
		sort();
	}

	template<GameMode TGameMode>
	std::string Hand<TGameMode>::toString() const
	{
		std::stringstream ss;
		for (auto i = 0u; i < cards.size(); ++i)
			ss << cards.at(i).toString();
		return ss.str();
	}

	template<GameMode TGameMode>
	std::ostream &operator<<(std::ostream &ostream, const Hand<TGameMode> &hand)
	{
		return ostream << hand.toString();
	}
}

#endif //KUHN_POKER_HAND_H
