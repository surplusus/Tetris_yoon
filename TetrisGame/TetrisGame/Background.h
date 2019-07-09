#pragma once
#include <vector>

class Background
{
public:
	const int basicPixel = 25;
	const int boardHeight = 15;
	const int boardWidth = 10;
	enum STATE { EMPTY = 0, FULL = 1 };
	using VECTORBOARD = std::vector<std::vector<STATE>>;
	using VECTORPILE = std::vector<POINT>;
private:
	VECTORBOARD _gameboard;
	VECTORBOARD _nextBlockBoard;
	VECTORPILE _piledBlock;
	int _cntLineDeleted = 0;	// count the number of the line deleted
public:
	Background();
public:
	void SetBoard(POINT pos, STATE state) { _gameboard[pos.y][pos.x] = state; }
	STATE GetBoard(POINT pos) { return _gameboard[pos.y][pos.x]; }
	void SetPile(POINT pos) { _piledBlock.push_back(pos); }
	VECTORPILE* GetPile() { return &_piledBlock; }
	bool CheckFullLine();
	void EraseLine(int idx);
};


