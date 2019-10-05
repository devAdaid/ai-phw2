#pragma once
#include "GameState.h"

class GameStrategy
{
public:
	GameStrategy();
	~GameStrategy();

	virtual int findBestPlace(GameState& gameState, int currentPlayer) { return -1; }
};

