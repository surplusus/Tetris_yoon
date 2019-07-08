#pragma once

class Background
{
public:
	enum STATE { EMPTY = 0, FULL = 1 };
private:
	const int basicPixel = 25;
private:
	STATE _gameboard[15][8] = { EMPTY, };
	STATE _nextBlockBoard[3][3] = { EMPTY, };
	bool _fullLine[15] = { EMPTY, };
	int _cntLineDeleted = 0;	// count the number of the line deleted
public:
	Background() {}

public:
	void SetBoard(POINT pos, STATE state) { _gameboard[pos.y][pos.x] = state; }
	STATE GetBoard(POINT pos) { return _gameboard[pos.y][pos.x]; }
	bool CheckFullLine();
	void EraseLine(int idx);
};


