#pragma once
#include "GameStrategy.h"
#include <map>

using namespace std;

class Minimax
	: public GameStrategy
{
public:
	Minimax();
	~Minimax();

	virtual int evaluate(GameState& game);
	pair<int, pair<int, int>> minPlayer(GameState& game);
	pair<int, pair<int, int>> maxPlayer(GameState& game);
	pair<int, int> findBestPlace(GameState& game, int currentPlayer) override;
};

