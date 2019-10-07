#include "GameState.h"
#include <iostream>

using namespace std;

GameState::GameState()
{
}

GameState::GameState(const GameState& other)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = other.board[i][j];
		}
	}
	depth = other.depth;
	winner = other.winner;
}

GameState::~GameState()
{
}

void GameState::print()
{
	cout << endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			char ch = 0;
			switch (board[i][j])
			{
			case EMPTY:
				ch = ' ';
				break;
			case PLAYER_A:
				ch = 'O';
				break;
			case PLAYER_B:
				ch = 'X';
			default:
				break;
			}
			cout << ch;
			
			if (j < BOARD_SIZE - 1)
			{
				cout << "|";
			}
		}
		cout << endl;
		
		if (i < BOARD_SIZE - 1)
		{
			for (int k = 0; k < BOARD_SIZE - 1; k++)
			{
				cout << "-+";
			}
			cout << "-" << endl;
		}
	}
	cout << endl;
}

bool GameState::isGameOver()
{
	return (winner != EMPTY) || (depth == BOARD_SIZE * BOARD_SIZE);
}

bool GameState::isMovable(pair<int, int> movement)
{
	return board[movement.first][movement.second] == EMPTY;
}

void GameState::move(pair<int, int> movement, int player)
{
	int x = movement.first;
	int y = movement.second;

	board[x][y] = player;
	depth += 1;

	// Check game over
	// 1 - Check row
	bool isFind = true;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (player != board[x][i])
		{
			isFind = false;
			break;
		}
	}
	if (isFind)
	{
		winner = player;
		return;
	}

	// 2 - Check col
	isFind = true;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (player != board[i][y])
		{
			isFind = false;
			break;
		}
	}
	if (isFind)
	{
		winner = player;
		return;
	}

	// 3 - Check d
	if (x == y)
	{
		isFind = true;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if (player != board[i][i])
			{
				isFind = false;
				break;
			}
		}

		if (isFind)
		{
			winner = player;
			return;
		}
	}
	
	if ((x + y) == (BOARD_SIZE - 1))
	{
		isFind = true;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			if (player != board[i][BOARD_SIZE - i - 1])
			{
				isFind = false;
				break;
			}
		}

		if (isFind)
		{
			winner = player;
			return;
		}
	}
}


void GameState::undo(pair<int, int> movement)
{
	board[movement.first][movement.second] = EMPTY;
	depth -= 1;
	winner = EMPTY;
}

vector<pair<int, int>> GameState::getPossibleMoves()
{
	vector<pair<int, int>> possibleMoves;
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			pair<int, int> movement = make_pair(i, j);
			if (isMovable(movement))
			{
				possibleMoves.push_back(movement);
			}
		}
	}

	return possibleMoves;
}