#ifndef KUHN_POKER_STATE_H
#define KUHN_POKER_STATE_H

#include "Hand.h"
#include "RuleSet/RuleSet.h"
#include "Types/PlayerIndex.h"
#include "Types/Turn.h"

namespace dpm
{
	template<GameMode TGameMode>
	struct State
	{
		using CommunityCards = std::array<Card, RuleSet<TGameMode>::getNumberOfCommunityCards()>;
		using PlayerCards = std::array<Hand<TGameMode>, RuleSet<TGameMode>::getNumberOfPlayers()>;
		using PreviousPlayerActions = std::array<PlayerAction, RuleSet<TGameMode>::getNumberOfPlayers()>;
		using Stakes = std::array<Cash, RuleSet<TGameMode>::getNumberOfPlayers()>;

		CommunityCards communityCards;
		int numberOfRaises;
		PlayerCards playerCards;
		PlayerIndex previousPlayer;
		PreviousPlayerActions previousPlayerActions;
		Stakes stakes;
		Round round;

		explicit State(const PlayerCards &playerCards, Cash smallBlind, Cash bigBlind);

		State(const CommunityCards &communityCards, const PlayerCards &playerCards, PlayerIndex previousPlayer,
		      PreviousPlayerActions previousPlayerActions, const Stakes &stakes, Round round);
	};

	template<GameMode TGameMode>
	State<TGameMode>::State(const State::PlayerCards &playerCards, const Cash smallBlind, const Cash bigBlind)
			: communityCards()
			, numberOfRaises(0)
			, playerCards(playerCards)
			, previousPlayer(PlayerIndices::Dealer)
			, previousPlayerActions()
			, stakes()
			, round(Rounds::Round1)
	{
		for (auto &previousAction: previousPlayerActions)
			previousAction = PlayerAction::NoAction;

		stakes.at(0) = smallBlind;
		stakes.at(1) = bigBlind;
	}

	template<GameMode TGameMode>
	State<TGameMode>::State(const State::CommunityCards &communityCards, const State::PlayerCards &playerCards,
	                        const PlayerIndex previousPlayer, PreviousPlayerActions previousPlayerActions,
	                        const State::Stakes &stakes, const Round round)
			: communityCards(communityCards)
			, numberOfRaises(0)
			, playerCards(playerCards)
			, previousPlayer(previousPlayer)
			, previousPlayerActions(previousPlayerActions)
			, stakes(stakes)
			, round(round)
	{
	}

}

#endif //KUHN_POKER_STATE_H
