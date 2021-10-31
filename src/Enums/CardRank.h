#ifndef KUHN_POKER_CARDRANK_H
#define KUHN_POKER_CARDRANK_H

namespace dpm
{
	using CardRankValue = std::uint8_t;

	enum class CardRank : CardRankValue
	{
		NoRank = 0,
		Two = 2,
		Three = 3,
		Four = 4,
		Five = 5,
		Six = 6,
		Seven = 7,
		Eight = 8,
		Nine = 9,
		Ten = 10,
		Jack = 11,
		Queen = 12,
		King = 13,
		Ace = 14
	};

	template<CardRank TCardRank>
	constexpr CardRankValue getCardRankValue()
	{
		return static_cast<CardRankValue>(TCardRank);
	}

}

#endif //KUHN_POKER_CARDRANK_H
