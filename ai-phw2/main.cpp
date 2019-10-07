#include <iostream>
#include "GameState.h"
#include "Minimax.h"
#include "AlphaBeta.h"
#include "GamePlayer.h"

using namespace std;

int main()
{
	GameState game = GameState();

	Minimax minimax = Minimax();
	AlphaBeta alphaBeta = AlphaBeta();

	GamePlayer playerA = GamePlayer(&alphaBeta, AI, PLAYER_A);
	GamePlayer playerB = GamePlayer(&alphaBeta, AI, PLAYER_B);

	GamePlayer* currentPlayer = &playerA;

	game.print();

	while (!game.isGameOver())
	{
		cout << "Current Turn: " << ((currentPlayer->playerNum == PLAYER_A) ? "A" : "B") << endl;
		
		currentPlayer->onTurn(game);

		game.print();

		if (currentPlayer == &playerA) currentPlayer = &playerB;
		else currentPlayer = &playerA;
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