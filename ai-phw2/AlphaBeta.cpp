#include "AlphaBeta.h"
#include <climits>
#include <algorithm>

using namespace std;

AlphaBeta::AlphaBeta()
{
}


AlphaBeta::~AlphaBeta()
{
}

int AlphaBeta::evaluate(GameState& game)
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

pair<int, pair<int, int>> AlphaBeta::minPlayer(GameState& game, int alpha, int beta)
{
	// If game is over, return profit
	if (game.isGameOver())
	{
		return make_pair(evaluate(game), make_pair(-1, -1));
	}

	// Set m
	int minProfit = INT_MAX;
	pair<int, int> bestMove;

	// For all next moves
	for (auto move : game.getPossibleMoves())
	{
		game.move(move, otherPlayer);
		int profit = maxPlayer(game, alpha, beta).first;
		if (profit < minProfit)
		{
			minProfit = profit;
			bestMove = move;

			beta = min(beta, minProfit);

			if (beta <= alpha)
			{
				game.undo(move);
				break;
			}
		}
		game.undo(move);
	}

	return make_pair(minProfit, bestMove);
}

pair<int, pair<int, int>> AlphaBeta::maxPlayer(GameState& game, int alpha, int beta)
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
		game.move(move, otherPlayer);
		int profit = minPlayer(game, alpha, beta).first;
		if (profit > maxProfit)
		{
			maxProfit = profit;
			bestMove = move;

			alpha = max(alpha, maxProfit);

			if (beta <= alpha)
			{
				game.undo(move);
				break;
			}
		}
		game.undo(move);
	}

	return make_pair(maxProfit, bestMove);
}

pair<int, int> AlphaBeta::findBestPlace(GameState& game, int currentPlayer)
{
	GameState origin = GameState(game);
	targetPlayer = currentPlayer;
	otherPlayer = 3 - currentPlayer;
	return (maxPlayer(origin, INT_MIN, INT_MAX)).second;
}