#include "Card.h"

namespace dpm
{
	std::string Card::toString(const CardSuit cardSuit)
	{
		switch(cardSuit)
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
		switch(cardRank)
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

	bool Card::operator==(const Card &card) const
	{
		return m_Rank == card.m_Rank && m_Suit == card.m_Suit;
	}

	bool Card::operator<(const Card &card) const
	{
		if (m_Rank != card.m_Rank)
			return m_Rank < card.m_Rank;
		else
			return m_Suit < card.m_Suit;
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
