#include "GamePlayer.h"
#include <iostream>

using namespace std;

GamePlayer::GamePlayer()
{
}

GamePlayer::GamePlayer(GameStrategy *strategy, int mode, int num)
{
	playStrategy = strategy;
	playMode = mode;
	playerNum = num;
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::onTurn(GameState &game)
{
	switch (playMode)
	{
	case HUMAN:
		cout << "Input: ";
		int x, y;
		cin >> x >> y;
		game.move(make_pair(x, y), playerNum);
		break;\
	case AI:
		cout << "Waiting AI..." << endl;
		pair<int, int> bestMove = playStrategy->findBestPlace(game, playerNum);
		game.move(bestMove, playerNum);
		cout << "x: " << bestMove.first << ", y: " << bestMove.second << endl;
		break;
	}
}