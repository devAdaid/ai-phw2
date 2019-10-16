#pragma once
#include "GameStrategy.h"
#include "MonteCarloGameState.h"

class MonteCarlo :
	public GameStrategy
{
public:
	MonteCarlo();
	~MonteCarlo();

	pair<int, int> findBestPlace(GameState& game, int currentPlayer) override;
	int monteCarloSearch(MonteCarloGameState *state, int player);
	int randomPlay(MonteCarloGameState& state, int player);
};

