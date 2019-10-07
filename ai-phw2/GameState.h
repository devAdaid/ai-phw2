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
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int depth = 0;
	int winner = EMPTY;
	pair<int, int> lastMove = make_pair(-1, -1);
	map<int, GameState> childs;

	GameState();
	GameState(const GameState& other);
	~GameState();

	void print();
	bool isGameOver();
	bool isMovable(pair<int, int> movement);
	void move(pair<int, int> movement, int player);
	void undo(pair<int, int> movement);
	vector<pair<int, int>> getPossibleMoves();
};

