#include "Card.h"

namespace dpm
{
	std::string Card::toString(const CardSuit cardSuit)
	{
		switch (cardSuit)
		{
			case CardSuit::NoSuit:
				return "N";
			case CardSuit::Club:
				return "C";
			case CardSuit::Diamond:
				return "D";
			case CardSuit::Heart:
				return "H";
			case CardSuit::Spade:
				return "S";
			default:
				return "X";
		}
	}

	std::string Card::toString(const CardRank cardRank)
	{
		switch (cardRank)
		{
			case CardRank::NoRank:
				return "N";
			case CardRank::Two:
				return "2";
			case CardRank::Three:
				return "3";
			case CardRank::Four:
				return "4";
			case CardRank::Five:
				return "5";
			case CardRank::Six:
				return "6";
			case CardRank::Seven:
				return "7";
			case CardRank::Eight:
				return "8";
			case CardRank::Nine:
				return "9";
			case CardRank::Ten:
				return "T";
			case CardRank::Jack:
				return "J";
			case CardRank::Queen:
				return "Q";
			case CardRank::King:
				return "K";
			case CardRank::Ace:
				return "A";
			default:
				return "X";
		}
	}

	CardSuit Card::parseCardSuit(const std::string_view suitString)
	{
		if (suitString.empty())
			return CardSuit::NoSuit;
		switch (suitString.at(0))
		{
			case 'c':
			case 'C':
				return CardSuit::Club;
			case 'd':
			case 'D':
				return CardSuit::Diamond;
			case 'h':
			case 'H':
				return CardSuit::Heart;
			case 's':
			case 'S':
				return CardSuit::Spade;
			default:
				return CardSuit::NoSuit;
		}
	}

	CardRank Card::parseCardRank(const std::string_view rankString)
	{
		if (rankString.empty())
			return CardRank::NoRank;
		switch (rankString.at(0))
		{
			case '2':
				return CardRank::Two;
			case '3':
				return CardRank::Three;
			case '4':
				return CardRank::Four;
			case '5':
				return CardRank::Five;
			case '6':
				return CardRank::Six;
			case '7':
				return CardRank::Seven;
			case '8':
				return CardRank::Eight;
			case '9':
				return CardRank::Nine;
			case 't':
			case 'T':
				return CardRank::Ten;
			case 'j':
			case 'J':
				return CardRank::Jack;
			case 'q':
			case 'Q':
				return CardRank::Queen;
			case 'k':
			case 'K':
				return CardRank::King;
			case 'a':
			case 'A':
				return CardRank::Ace;
			default:
				return CardRank::NoRank;
		}
	}

	Card Card::parseCard(const std::string_view cardString)
	{
		if (cardString.size() < 2)
			return NoCard();
		return {parseCardSuit(cardString.substr(0, 1)), parseCardRank(cardString.substr(1, 1))};
	}

	bool Card::operator==(const Card &card) const
	{
		return m_Rank == card.m_Rank && m_Suit == card.m_Suit;
	}

	bool Card::operator!=(const Card &card) const
	{
		return m_Rank != card.m_Rank || m_Suit != card.m_Suit;
	}

	bool Card::operator<(const Card &card) const
	{
		if (m_Rank != card.m_Rank)
			return m_Rank < card.m_Rank;
		else
			return m_Suit < card.m_Suit;
	}

	CardRank Card::getRank() const
	{
		return m_Rank;
	}

	CardSuit Card::getSuit() const
	{
		return m_Suit;
	}

	bool Card::isEmpty() const
	{
		return m_Rank == CardRank::NoRank && m_Suit == CardSuit::NoSuit;
	}

	std::string Card::toString() const
	{
		return toString(m_Suit) + toString(m_Rank);
	}
}
