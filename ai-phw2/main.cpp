#include <iostream>
#include "GameState.h"
#include "MinimaxStrategy.h"

using namespace std;

int main()
{
	GameState game = GameState();
	int bestMove = -1;
	int currentPlayer = PLAYER_A;

	MinimaxStrategy minimax = MinimaxStrategy();

	while (!game.isGameOver())
	{
		cout << "Current Turn: " << ((currentPlayer == PLAYER_A) ? "A" : "B") << endl;
		bestMove = minimax.findBestPlace(game, currentPlayer);
		game.move(bestMove, currentPlayer);

		int x = bestMove / BOARD_SIZE;
		int y = bestMove % BOARD_SIZE;
		cout << "x: " << x << ", y: " << y << endl;
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