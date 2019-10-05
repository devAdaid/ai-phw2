#include "MinimaxStrategy.h"
#include <climits>
#include <vector>
#include <iostream>

using namespace std;

MinimaxStrategy::MinimaxStrategy()
{
}


MinimaxStrategy::~MinimaxStrategy()
{
}

int MinimaxStrategy::evaluate(GameState& game, int targetPlayer)
{
	int value = 0;
	if (game.winner == targetPlayer)
	{
		value = 1;
	}
	else if (game.winner == EMPTY)
	{
		value = 0;
	}
	else
	{
		value = -1;
	}
	return value;
}

pair<int, int> MinimaxStrategy::minPlayer(GameState& game, int targetPlayer, int otherPlayer)
{
	// If game is over, return profit
	if (game.isGameOver())
	{
		return make_pair(evaluate(game, targetPlayer), game.lastMove);
	}

	// Set m
	int min = INT_MAX;
	int minMove = -1;

	// For all next moves
	game.makeChildren(otherPlayer);
	for (auto iter = game.childs.begin(); iter != game.childs.end(); iter++)
	{
		int m = (maxPlayer(iter->second, targetPlayer, otherPlayer)).first;
		if (m < min)
		{
			min = m;
			minMove = iter->first;
		}
	}

	return make_pair(min, minMove);
}

pair<int, int> MinimaxStrategy::maxPlayer(GameState& game, int targetPlayer, int otherPlayer)
{
	// If game is over, return profit
	if (game.isGameOver())
	{
		return make_pair(evaluate(game, targetPlayer), game.lastMove);
	}

	// Set m
	int max = INT_MIN;
	int maxMove = -1;

	// For all next moves
	game.makeChildren(targetPlayer);
	for (auto iter = game.childs.begin(); iter != game.childs.end(); iter++)
	{
		int m = (minPlayer(iter->second, targetPlayer, otherPlayer)).first;
		if (m > max)
		{
			max = m;
			maxMove = iter->first;
		}
	}

	return make_pair(max, maxMove);
}

int MinimaxStrategy::findBestPlace(GameState& game, int currentPlayer)
{
	GameState origin = GameState(game);
	return (maxPlayer(origin, currentPlayer, 3 - currentPlayer)).second;
}