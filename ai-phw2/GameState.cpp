#include "GameState.h"



GameState::GameState()
{
}

GameState::GameState(const GameState& other)
{
	int count = BOARD_SIZE * BOARD_SIZE;
	for (int i = 0; i < count; i++)
	{
		board[i] = other.board[i];
	}
	depth = other.depth;
	winner = other.winner;
	lastMove = other.lastMove;
}

GameState::~GameState()
{
}

int& GameState::placeAt(int x, int y)
{
	return board[x*BOARD_SIZE + y];
}

bool GameState::isGameOver()
{
	return (winner != EMPTY) || (depth == BOARD_SIZE * BOARD_SIZE);
}

bool GameState::isMovable(int idx)
{
	return board[idx] == EMPTY;
}

void GameState::move(int idx, int player)
{
	board[idx] = player;
	lastMove = idx;
	depth += 1;

	// Check game over
	int x = idx / BOARD_SIZE;
	int y = idx % BOARD_SIZE;

	// 1 - Check row
	bool isFind = true;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (player != placeAt(x, i))
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
		if (player != placeAt(i, y))
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
			if (player != placeAt(i, i))
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
			if (player != placeAt(i, BOARD_SIZE - i - 1))
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

void GameState::makeChildren(int player)
{
	int count = BOARD_SIZE * BOARD_SIZE;
	for (int i = 0; i < count; i++)
	{
		if (isMovable(i))
		{
			childs.insert(make_pair(i, getMovedState(i, player)));
		}
	}
}

GameState GameState::getMovedState(int idx, int player)
{
	GameState movedState = GameState(*this);

	if (isMovable(idx))
	{
		movedState.move(idx, player);
	}

	return movedState;
}

vector<int> GameState::getPossibleMoves(int player)
{
	vector<int> possibleMoves;

	int count = BOARD_SIZE * BOARD_SIZE;
	for (int i = 0; i < count; i++)
	{
		if (isMovable(i))
		{
			possibleMoves.push_back(i);
		}
	}

	return possibleMoves;
}