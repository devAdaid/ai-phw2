#pragma once
#include "GameState.h"
#include <vector>
#include <map>
#define UCT_CONSTANT 0.4

class MonteCarloGameState :
	public GameState
{
public:
	int visitCount = 0;
	float winCount = 0;
	vector<pair<int, int>> notExpandedMoves;
	map<pair<int,int>, MonteCarloGameState> childs;

	MonteCarloGameState();
	MonteCarloGameState(const GameState& other);
	~MonteCarloGameState();

	bool isAllExpanded();
	MonteCarloGameState randomExpandedChild(int player);
	MonteCarloGameState& selectChildByUCT();
	pair<int, int> getBestMove();
	bool visit(int player);
	void randomMove(int player);
	float calculateUctWith(int parentVisitCount);
};

