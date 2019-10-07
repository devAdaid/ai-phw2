#pragma once
#include "GameState.h"

class GameStrategy
{
public:
	GameStrategy();
	~GameStrategy();
	int targetPlayer = 0;
	int otherPlayer = 0;

	virtual pair<int, int> findBestPlace(GameState& gameState, int currentPlayer) = 0;
};

