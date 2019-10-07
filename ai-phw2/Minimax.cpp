#include "Minimax.h"
#include <climits>
#include <vector>
#include <iostream>

using namespace std;

Minimax::Minimax()
{
}


Minimax::~Minimax()
{
}

int Minimax::evaluate(GameState& game)
{
	int value = -game.depth;
	if (game.winner == targetPlayer)
	{
		value += 100;
	}
	else if (game.winner == otherPlayer)
	{
		value -= 100;
	}
	return value;
}

pair<int, pair<int, int>> Minimax::minPlayer(GameState& game)
{
	// If game is over, return profit
	if (game.isGameOver())
	{
		//game.print();
		return make_pair(evaluate(game), make_pair(-1, -1));
	}

	// Set m
	int minProfit = INT_MAX;
	pair<int, int> bestMove;

	// For all next moves
	for (auto move : game.getPossibleMoves())
	{
		game.move(move, otherPlayer);
		int profit = maxPlayer(game).first;
		if (profit < minProfit)
		{
			minProfit = profit;
			bestMove = move;
		}
		game.undo(move);
	}

	return make_pair(minProfit, bestMove);
}

pair<int, pair<int, int>> Minimax::maxPlayer(GameState& game)
{
	// If game is over, return profit
	if (game.isGameOver())
	{
		return make_pair(evaluate(game), make_pair(-1, -1));
	}

	// Set m
	int maxProfit = INT_MIN;
	pair<int, int> bestMove;

	// For all next moves
	for (auto move : game.getPossibleMoves())
	{
		game.move(move, targetPlayer);
		int profit = minPlayer(game).first;
		if (profit > maxProfit)
		{
			maxProfit = profit;
			bestMove = move;
		}
		game.undo(move);

		if (game.depth == 0)
		{
			cout << "." << endl;
		}
	}

	return make_pair(maxProfit, bestMove);
}

pair<int, int> Minimax::findBestPlace(GameState& game, int currentPlayer)
{
	GameState origin = GameState(game);
	targetPlayer = currentPlayer;
	otherPlayer = 3 - targetPlayer;
	return (maxPlayer(origin)).second;
}