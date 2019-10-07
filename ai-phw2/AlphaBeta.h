#pragma once
#include "Minimax.h"

class AlphaBeta :
	public Minimax
{
public:
	AlphaBeta();
	~AlphaBeta();

	virtual int evaluate(GameState& game) override;
	pair<int, pair<int, int>> minPlayer(GameState& game, int alpha, int beta);
	pair<int, pair<int, int>> maxPlayer(GameState& game, int alpha, int beta);
	pair<int, int> findBestPlace(GameState& game, int currentPlayer) override;
};

