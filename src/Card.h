#ifndef KUHN_POKER_CARD_H
#define KUHN_POKER_CARD_H

#include "Enums/CardRank.h"
#include "Enums/CardSuit.h"

namespace dpm
{
	class Card
	{
	public:
		// --- NoCard ---
		[[nodiscard]] static constexpr Card NoCard();

		// --- Clubs ---
		[[nodiscard]] static constexpr Card ClubTwo();

		[[nodiscard]] static constexpr Card ClubThree();

		[[nodiscard]] static constexpr Card ClubFour();

		[[nodiscard]] static constexpr Card ClubFive();

		[[nodiscard]] static constexpr Card ClubSix();

		[[nodiscard]] static constexpr Card ClubSeven();

		[[nodiscard]] static constexpr Card ClubEight();

		[[nodiscard]] static constexpr Card ClubNine();

		[[nodiscard]] static constexpr Card ClubTen();

		[[nodiscard]] static constexpr Card ClubJack();

		[[nodiscard]] static constexpr Card ClubQueen();

		[[nodiscard]] static constexpr Card ClubKing();

		[[nodiscard]] static constexpr Card ClubAce();

		// --- Diamonds ---
		[[nodiscard]] static constexpr Card DiamondTwo();

		[[nodiscard]] static constexpr Card DiamondThree();

		[[nodiscard]] static constexpr Card DiamondFour();

		[[nodiscard]] static constexpr Card DiamondFive();

		[[nodiscard]] static constexpr Card DiamondSix();

		[[nodiscard]] static constexpr Card DiamondSeven();

		[[nodiscard]] static constexpr Card DiamondEight();

		[[nodiscard]] static constexpr Card DiamondNine();

		[[nodiscard]] static constexpr Card DiamondTen();

		[[nodiscard]] static constexpr Card DiamondJack();

		[[nodiscard]] static constexpr Card DiamondQueen();

		[[nodiscard]] static constexpr Card DiamondKing();

		[[nodiscard]] static constexpr Card DiamondAce();

		// --- Hearts ---
		[[nodiscard]] static constexpr Card HeartTwo();

		[[nodiscard]] static constexpr Card HeartThree();

		[[nodiscard]] static constexpr Card HeartFour();

		[[nodiscard]] static constexpr Card HeartFive();

		[[nodiscard]] static constexpr Card HeartSix();

		[[nodiscard]] static constexpr Card HeartSeven();

		[[nodiscard]] static constexpr Card HeartEight();

		[[nodiscard]] static constexpr Card HeartNine();

		[[nodiscard]] static constexpr Card HeartTen();

		[[nodiscard]] static constexpr Card HeartJack();

		[[nodiscard]] static constexpr Card HeartQueen();

		[[nodiscard]] static constexpr Card HeartKing();

		[[nodiscard]] static constexpr Card HeartAce();

		// --- Spades ---
		[[nodiscard]] static constexpr Card SpadeTwo();

		[[nodiscard]] static constexpr Card SpadeThree();

		[[nodiscard]] static constexpr Card SpadeFour();

		[[nodiscard]] static constexpr Card SpadeFive();

		[[nodiscard]] static constexpr Card SpadeSix();

		[[nodiscard]] static constexpr Card SpadeSeven();

		[[nodiscard]] static constexpr Card SpadeEight();

		[[nodiscard]] static constexpr Card SpadeNine();

		[[nodiscard]] static constexpr Card SpadeTen();

		[[nodiscard]] static constexpr Card SpadeJack();

		[[nodiscard]] static constexpr Card SpadeQueen();

		[[nodiscard]] static constexpr Card SpadeKing();

		[[nodiscard]] static constexpr Card SpadeAce();

		[[nodiscard]] static std::string toString(CardSuit cardSuit);

		[[nodiscard]] static std::string toString(CardRank cardRank);

		[[nodiscard]] static CardSuit parseCardSuit(std::string_view suitString);

		[[nodiscard]] static CardRank parseCardRank(std::string_view rankString);

		[[nodiscard]] static Card parseCard(std::string_view cardString);

	public:
		constexpr Card();

		constexpr Card(CardSuit suit, CardRank rank);

		bool operator==(const Card &card) const;

		bool operator!=(const Card &card) const;

		bool operator<(const Card &card) const;

		[[nodiscard]] CardRank getRank() const;

		[[nodiscard]] CardSuit getSuit() const;

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] std::string toString() const;

	private:
		CardSuit m_Suit;
		CardRank m_Rank;
	};

	constexpr Card Card::NoCard() { return {CardSuit::NoSuit, CardRank::NoRank}; }

	constexpr Card Card::ClubTwo() { return {CardSuit::Club, CardRank::Two}; }

	constexpr Card Card::ClubThree() { return {CardSuit::Club, CardRank::Three}; }

	constexpr Card Card::ClubFour() { return {CardSuit::Club, CardRank::Four}; }

	constexpr Card Card::ClubFive() { return {CardSuit::Club, CardRank::Five}; }

	constexpr Card Card::ClubSix() { return {CardSuit::Club, CardRank::Six}; }

	constexpr Card Card::ClubSeven() { return {CardSuit::Club, CardRank::Seven}; }

	constexpr Card Card::ClubEight() { return {CardSuit::Club, CardRank::Eight}; }

	constexpr Card Card::ClubNine() { return {CardSuit::Club, CardRank::Nine}; }

	constexpr Card Card::ClubTen() { return {CardSuit::Club, CardRank::Ten}; }

	constexpr Card Card::ClubJack() { return {CardSuit::Club, CardRank::Jack}; }

	constexpr Card Card::ClubQueen() { return {CardSuit::Club, CardRank::Queen}; }

	constexpr Card Card::ClubKing() { return {CardSuit::Club, CardRank::King}; }

	constexpr Card Card::ClubAce() { return {CardSuit::Club, CardRank::Ace}; }

	constexpr Card Card::DiamondTwo() { return {CardSuit::Diamond, CardRank::Two}; }

	constexpr Card Card::DiamondThree() { return {CardSuit::Diamond, CardRank::Three}; }

	constexpr Card Card::DiamondFour() { return {CardSuit::Diamond, CardRank::Four}; }

	constexpr Card Card::DiamondFive() { return {CardSuit::Diamond, CardRank::Five}; }

	constexpr Card Card::DiamondSix() { return {CardSuit::Diamond, CardRank::Six}; }

	constexpr Card Card::DiamondSeven() { return {CardSuit::Diamond, CardRank::Seven}; }

	constexpr Card Card::DiamondEight() { return {CardSuit::Diamond, CardRank::Eight}; }

	constexpr Card Card::DiamondNine() { return {CardSuit::Diamond, CardRank::Nine}; }

	constexpr Card Card::DiamondTen() { return {CardSuit::Diamond, CardRank::Ten}; }

	constexpr Card Card::DiamondJack() { return {CardSuit::Diamond, CardRank::Jack}; }

	constexpr Card Card::DiamondQueen() { return {CardSuit::Diamond, CardRank::Queen}; }

	constexpr Card Card::DiamondKing() { return {CardSuit::Diamond, CardRank::King}; }

	constexpr Card Card::DiamondAce() { return {CardSuit::Diamond, CardRank::Ace}; }

	constexpr Card Card::HeartTwo() { return {CardSuit::Heart, CardRank::Two}; }

	constexpr Card Card::HeartThree() { return {CardSuit::Heart, CardRank::Three}; }

	constexpr Card Card::HeartFour() { return {CardSuit::Heart, CardRank::Four}; }

	constexpr Card Card::HeartFive() { return {CardSuit::Heart, CardRank::Five}; }

	constexpr Card Card::HeartSix() { return {CardSuit::Heart, CardRank::Six}; }

	constexpr Card Card::HeartSeven() { return {CardSuit::Heart, CardRank::Seven}; }

	constexpr Card Card::HeartEight() { return {CardSuit::Heart, CardRank::Eight}; }

	constexpr Card Card::HeartNine() { return {CardSuit::Heart, CardRank::Nine}; }

	constexpr Card Card::HeartTen() { return {CardSuit::Heart, CardRank::Ten}; }

	constexpr Card Card::HeartJack() { return {CardSuit::Heart, CardRank::Jack}; }

	constexpr Card Card::HeartQueen() { return {CardSuit::Heart, CardRank::Queen}; }

	constexpr Card Card::HeartKing() { return {CardSuit::Heart, CardRank::King}; }

	constexpr Card Card::HeartAce() { return {CardSuit::Heart, CardRank::Ace}; }

	constexpr Card Card::SpadeTwo() { return {CardSuit::Spade, CardRank::Two}; }

	constexpr Card Card::SpadeThree() { return {CardSuit::Spade, CardRank::Three}; }

	constexpr Card Card::SpadeFour() { return {CardSuit::Spade, CardRank::Four}; }

	constexpr Card Card::SpadeFive() { return {CardSuit::Spade, CardRank::Five}; }

	constexpr Card Card::SpadeSix() { return {CardSuit::Spade, CardRank::Six}; }

	constexpr Card Card::SpadeSeven() { return {CardSuit::Spade, CardRank::Seven}; }

	constexpr Card Card::SpadeEight() { return {CardSuit::Spade, CardRank::Eight}; }

	constexpr Card Card::SpadeNine() { return {CardSuit::Spade, CardRank::Nine}; }

	constexpr Card Card::SpadeTen() { return {CardSuit::Spade, CardRank::Ten}; }

	constexpr Card Card::SpadeJack() { return {CardSuit::Spade, CardRank::Jack}; }

	constexpr Card Card::SpadeQueen() { return {CardSuit::Spade, CardRank::Queen}; }

	constexpr Card Card::SpadeKing() { return {CardSuit::Spade, CardRank::King}; }

	constexpr Card Card::SpadeAce() { return {CardSuit::Spade, CardRank::Ace}; }

	constexpr Card::Card()
			: m_Suit(CardSuit::NoSuit)
			, m_Rank(CardRank::NoRank)
	{
	}

	constexpr Card::Card(const CardSuit suit, const CardRank rank)
			: m_Suit(suit)
			, m_Rank(rank)
	{
	}

}

#endif //KUHN_POKER_CARD_H
