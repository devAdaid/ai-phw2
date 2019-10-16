#include "MonteCarloGameState.h"
#include <cmath>
#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;

MonteCarloGameState::MonteCarloGameState()
{
}

MonteCarloGameState::MonteCarloGameState(const GameState& other)
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


MonteCarloGameState::~MonteCarloGameState()
{
}

bool MonteCarloGameState::visit(int player)
{
	bool isFirstVisit = false;

	// if first visit
	if (visitCount == 0)
	{
		notExpandedMoves = getPossibleMoves();
		isFirstVisit = true;
	}

	visitCount += 1;

	return isFirstVisit;
}

void MonteCarloGameState::randomMove(int player)
{
	auto possibleMoves = getPossibleMoves();
	int randMax = possibleMoves.size();
	int randIdx = rand() % randMax;
	auto randMove = possibleMoves[randIdx];
	move(randMove, player);
}

bool MonteCarloGameState::isAllExpanded()
{
	return notExpandedMoves.size() == 0;
}

MonteCarloGameState MonteCarloGameState::randomExpandedChild(int player)
{
	int randMax = notExpandedMoves.size();
	int randIdx = rand() % randMax;
	auto randMove = notExpandedMoves[randIdx];

	MonteCarloGameState newChild = MonteCarloGameState();
	newChild.move(randMove, player);
	childs.insert(make_pair(notExpandedMoves[randIdx], newChild));
	notExpandedMoves.erase(notExpandedMoves.begin() + randIdx);
	return newChild;
}

MonteCarloGameState& MonteCarloGameState::selectChildByUCT()
{
	float maxUct = INT_MIN;
	MonteCarloGameState* bestChild = nullptr;

	for (auto iter = childs.begin(); iter != childs.end(); iter++)
	{
		MonteCarloGameState& child = iter->second;
		float childUct = child.calculateUctWith(visitCount);

		if (childUct > maxUct)
		{
			maxUct = childUct;
			bestChild = &child;
		}
	}

	return *bestChild;
}

pair<int, int> MonteCarloGameState::getBestMove()
{
	float maxWinRate = -1;
	pair<int, int> bestMove;

	for (auto iter = childs.begin(); iter != childs.end(); iter++)
	{
		MonteCarloGameState& child = iter->second;
		float winRate = (float)child.winCount / child.visitCount;

		if (winRate > maxWinRate)
		{
			maxWinRate = winRate;
			bestMove = iter->first;
		}
	}

	return bestMove;
}

float MonteCarloGameState::calculateUctWith(int parentVisitCount)
{
	float uct = INT_MAX;

	if(visitCount > 0)
	{
		float averageReward = (float)winCount / visitCount;
		uct = averageReward + 2 * UCT_CONSTANT * sqrt(2 * log(parentVisitCount) / visitCount);	
	}
	return uct;
}