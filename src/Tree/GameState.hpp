#ifndef POKER_GAMESTATE_HPP
#define POKER_GAMESTATE_HPP

#include "Tree/ChildInfo.hpp"
#include "Tree/RoundState.hpp"
#include "Tree/State.h"

namespace dpm
{

	template<GameMode TGameMode>
	class GameState : public State<TGameMode>
	{
	public:
		static GameState *createGameState(State<TGameMode> &&state);

	public:
		GameState();

		GameState(const GameState &gameState) = default;

		explicit GameState(State<TGameMode> &&state);

		[[nodiscard]] GameStateType getGameStateType() const override;

		[[nodiscard]]
		const std::array<ChildInfo<TGameMode>, NUMBER_OF_PLAYER_ACTIONS> &getChildren() const;

		void generateChildren(const TurnOptions<TGameMode> &turnOptions);

		[[nodiscard]]
		typename InformationSet<TGameMode>::PossiblePlayerActions getPlayerActions() const;

	private:
		static std::vector<std::unique_ptr<GameState>> s_GameStates;

	private:
		std::array<ChildInfo<TGameMode>, NUMBER_OF_PLAYER_ACTIONS> m_Children;
	};

	template<GameMode TGameMode>
	std::vector<std::unique_ptr<GameState<TGameMode>>> GameState<TGameMode>::s_GameStates = {};

	template<GameMode TGameMode>
	GameState<TGameMode> *GameState<TGameMode>::createGameState(State<TGameMode> &&state)
	{
		s_GameStates.push_back(std::make_unique<GameState<TGameMode>>(std::move(state)));
		return s_GameStates.back().get();
	}

	template<GameMode TGameMode>
	GameState<TGameMode>::GameState()
			: State<TGameMode>()
			, m_Children()
	{
	}

	template<GameMode TGameMode>
	GameState<TGameMode>::GameState(State<TGameMode> &&state)
			: State<TGameMode>(std::move(state))
			, m_Children()
	{
	}

	template<GameMode TGameMode>
	GameStateType GameState<TGameMode>::getGameStateType() const
	{
		return GameStateType::PLAYER_MOVE;
	}

	template<GameMode TGameMode>
	const std::array<ChildInfo<TGameMode>, NUMBER_OF_PLAYER_ACTIONS> &GameState<TGameMode>::getChildren() const
	{
		return m_Children;
	}

	template<GameMode TGameMode>
	void GameState<TGameMode>::generateChildren(const TurnOptions<TGameMode> &turnOptions)
	{
		for (auto i = 0u; i < NUMBER_OF_PLAYER_ACTIONS; ++i)
		{
			auto &playerMove = turnOptions.possiblePlayerMoves.at(i);
			if (playerMove.playerAction == PlayerAction::NoAction)
				continue;
			this->generateChild(&m_Children.at(i), std::move(playerMove), turnOptions.nextPlayer);
		}
	}

	template<GameMode TGameMode>
	typename InformationSet<TGameMode>::PossiblePlayerActions GameState<TGameMode>::getPlayerActions() const
	{
		std::array<PlayerAction, NUMBER_OF_PLAYER_ACTIONS> playerActions = {};
		for (auto i = 0u; i < m_Children.size(); ++i)
			playerActions.at(i) = m_Children.at(i).playerMove.playerAction;
		return playerActions;
	}

}

#endif //POKER_GAMESTATE_HPP
