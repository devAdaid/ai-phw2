#pragma once
#define BOARD_SIZE 3
#include <vector>
#include <map>

using namespace std;

enum PlaceState
{
	EMPTY,
	PLAYER_A,
	PLAYER_B
};

class GameState
{
public:
	int board[BOARD_SIZE * BOARD_SIZE] = { 0 };
	int depth = 0;
	int winner = EMPTY;
	int lastMove = -1;
	map<int, GameState> childs;

	GameState();
	GameState(const GameState& other);
	~GameState();

	int& placeAt(int x, int y);
	bool isGameOver();
	bool isMovable(int idx);
	void move(int idx, int player);
	void makeChildren(int player);
	GameState getMovedState(int idx, int player);
	vector<int> getPossibleMoves(int player);
};

