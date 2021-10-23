#ifndef KUHN_POKER_NODEBASE_H
#define KUHN_POKER_NODEBASE_H

#include "Outcome.h"
#include "State.h"


namespace dpm
{
	class Player;

	using ReachProbabilities = std::array<float, Moves::getNumberOfMoves()>;

	class NodeBase
	{
	public:
		NodeBase();

		explicit NodeBase(State &&state);

		virtual ~NodeBase();

		[[nodiscard]] virtual Outcome getOutcome(const History &history) const = 0;

		virtual float cfr(const std::array<Player *, PlayerIndices::getNumberOfPlayers()> &players,
		                  PlayerIndex activePlayer,
		                  const Hands &hands,
		                  const History &history,
		                  ReachProbabilities reachProbabilities,
		                  int playerIndexToUpdate) const = 0;

	protected:
		State m_State;

	protected:
		[[nodiscard]] unsigned int getHistoryIndex() const;
	};
}

#endif //KUHN_POKER_NODEBASE_H
