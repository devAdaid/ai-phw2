#include <iostream>
#include "GameState.h"
#include "Minimax.h"
#include "AlphaBeta.h"

using namespace std;

int main()
{
	GameState game = GameState();
	pair<int, int> bestMove;
	int currentPlayer = PLAYER_A;

	Minimax minimax = Minimax();
	AlphaBeta alphaBeta = AlphaBeta();

	GameStrategy& strategy = alphaBeta;

	game.print();

	while (!game.isGameOver())
	{
		cout << "Current Turn: " << ((currentPlayer == PLAYER_A) ? "A" : "B") << endl;
		if (currentPlayer == PLAYER_A)
		{
			cout << "Waiting AI..." << endl;
			bestMove = strategy.findBestPlace(game, currentPlayer);
			game.move(bestMove, currentPlayer);

			int x = bestMove.first;
			int y = bestMove.second;
			cout << "x: " << x << ", y: " << y << endl;
		}
		else
		{
			cout << "Input: ";
			
			int x, y;
			cin >> x >> y;
			game.move(make_pair(x, y), currentPlayer);
		}
		/*
		cout << "Waiting AI..." << endl;
		bestMove = strategy.findBestPlace(game, currentPlayer);
		game.move(bestMove, currentPlayer);
		int x = bestMove.first;
		int y = bestMove.second;
		cout << "x: " << x << ", y: " << y << endl;
		*/

		game.print();
		currentPlayer = 3 - currentPlayer;
	}

	switch (game.winner)
	{
	case EMPTY:
		cout << "Draw" << endl;
		break;
	case PLAYER_A:
		cout << "A win" << endl;
		break;
	case PLAYER_B:
		cout << "B win" << endl;
		break;
	default:
		break;
	}

	return 0;
}