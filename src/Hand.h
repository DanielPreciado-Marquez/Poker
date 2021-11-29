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
		std::array<Card, RuleSet<TGameMode>::NUMBER_OF_CARDS_PER_PLAYER> cards;

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
	bool operator==(const Hand<TGameMode> &handA, const Hand<TGameMode> &handB);

	template<GameMode TGameMode>
	bool operator!=(const Hand<TGameMode> &handA, const Hand<TGameMode> &handB);

	template<GameMode TGameMode>
	bool operator<(const Hand<TGameMode> &handA, const Hand<TGameMode> &handB);

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
		for (const auto &handCard: cards)
			if (handCard == card)
				return true;
		return false;
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
	bool operator<(const Hand<TGameMode> &handA, const Hand<TGameMode> &handB)
	{
		auto sumA = 0;
		auto sumB = 0;
		// TODO compare Hands
		for (const auto &card: handA.cards)
			sumA += getCardRankValue(card.getRank());
		for (const auto &card: handB.cards)
			sumB += getCardRankValue(card.getRank());

		return sumA < sumB;
	}

	template<GameMode TGameMode>
	std::ostream &operator<<(std::ostream &ostream, const Hand<TGameMode> &hand)
	{
		return ostream << hand.toString();
	}

	template<GameMode TGameMode>
	bool operator==(const Hand<TGameMode> &handA, const Hand<TGameMode> &handB)
	{
		for (auto i = 0u; i < handA.size(); ++i)
			if (handA.cards.at(i) != handB.cards.at(i))
				return false;
		return true;
	}

	template<GameMode TGameMode>
	bool operator!=(const Hand<TGameMode> &handA, const Hand<TGameMode> &handB)
	{
		for (auto i = 0u; i < handA.size(); ++i)
			if (handA.cards.at(i) != handB.cards.at(i))
				return true;
		return false;
	}
}

#endif //KUHN_POKER_HAND_H
