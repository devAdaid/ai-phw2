#include "MonteCarlo.h"
#include <cstdlib>
#include <ctime>

MonteCarlo::MonteCarlo()
{
}


MonteCarlo::~MonteCarlo()
{
}

pair<int, int> MonteCarlo::findBestPlace(GameState& game, int currentPlayer)
{
	srand((unsigned int)time(0));

	MonteCarloGameState origin = MonteCarloGameState(game);
	targetPlayer = currentPlayer;
	otherPlayer = 3 - targetPlayer;

	for (int i = 0; i < 10000; i++)
	{
		monteCarloSearch(&origin, currentPlayer);
	}

	return origin.getBestMove();
}

int MonteCarlo::monteCarloSearch(MonteCarloGameState *state, int player)
{
	bool isFirstVisit = state->visit(player);

	int winner = 0;
	if (state->isAllExpanded())
	{
		MonteCarloGameState& nextState = state->selectChildByUCT();
		winner = monteCarloSearch(&nextState, 3 - player);
	}
	else
	{
		MonteCarloGameState nextState = state->randomExpandedChild(player);
		winner = randomPlay(nextState, 3 - player);
	}

	if (winner == targetPlayer)
	{
		state->winCount += 1;
	}
	else if (winner == EMPTY)
	{
		state->winCount += 0.5;
	}

	return winner;
}

int MonteCarlo::randomPlay(MonteCarloGameState& state, int player)
{
	if (state.isGameOver())
	{
		return state.winner;
	}

	state.randomMove(player);
	return randomPlay(state, 3 - player);
}
