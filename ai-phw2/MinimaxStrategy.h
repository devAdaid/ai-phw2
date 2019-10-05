#pragma once
#include "GameStrategy.h"
#include <map>

using namespace std;

class MinimaxStrategy
	: public GameStrategy
{
public:
	MinimaxStrategy();
	~MinimaxStrategy();

	int evaluate(GameState& game, int targetPlayer);
	pair<int,int> minPlayer(GameState& game, int targetPlayer, int otherPlayer);
	pair<int, int> maxPlayer(GameState& game, int targetPlayer, int otherPlayer);
	int findBestPlace(GameState& game, int currentPlayer) override;
};

