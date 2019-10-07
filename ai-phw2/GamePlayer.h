#pragma once
#include "GameStrategy.h"
#include "GameState.h"

enum AIMode
{
	NONE,
	AI,
	HUMAN
};

class GamePlayer
{
public:
	GameStrategy *playStrategy;
	int playMode = 0;
	int playerNum = 0;

	GamePlayer();
	GamePlayer(GameStrategy *strategy, int mode, int num);
	~GamePlayer();

	void onTurn(GameState &game);
};

