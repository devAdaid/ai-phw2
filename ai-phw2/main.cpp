#include <iostream>
#include "GameState.h"
#include "Minimax.h"
#include "AlphaBeta.h"
#include "GamePlayer.h"
#include "MonteCarlo.h"

using namespace std;

int main()
{
	GameState game = GameState();

	Minimax minimax = Minimax();
	AlphaBeta alphaBeta = AlphaBeta();
	MonteCarlo monteCarlo = MonteCarlo();

	GamePlayer playerA = GamePlayer(nullptr, HUMAN, PLAYER_A);
	GamePlayer playerB = GamePlayer(nullptr, HUMAN, PLAYER_B);

	GamePlayer* currentPlayer = &playerA;

#pragma region Set PlayerA
	int player;
	cout << "Select Player A's type" << endl
		<< "(1:Human input, 2:Minimax, 3:Alphabeta, 4: Monte Carlo): ";
	cin >> player;
	switch (player)
	{
	case 2:
		playerA = GamePlayer(&minimax, AI, PLAYER_A);
		break;
	case 3:
		playerA = GamePlayer(&alphaBeta, AI, PLAYER_A);
		break;
	case 4:
		playerA = GamePlayer(&monteCarlo, AI, PLAYER_A);
		break;
	default:
		break;
	}
#pragma endregion

#pragma region Set PlayerB
	cout << "Select Player B's type" << endl
		<< "(1:Human input, 2:Minimax, 3:Alphabeta, 4: Monte Carlo): ";
	cin >> player;
	switch (player)
	{
	case 2:
		playerB = GamePlayer(&minimax, AI, PLAYER_B);
		break;
	case 3:
		playerB = GamePlayer(&alphaBeta, AI, PLAYER_B);
		break;
	case 4:
		playerB = GamePlayer(&monteCarlo, AI, PLAYER_B);
		break;
	default:
		break;
	}
#pragma endregion

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