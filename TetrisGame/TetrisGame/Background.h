#pragma once

class Background
{
private:
	const int basicPixel = 25;
	enum STATE{EMPTY = 0, FULL = 1};
private:
	STATE _gameboard[12][8] = { EMPTY, };
	STATE _nextBlockBoard[4][4] = { EMPTY, };
	bool _fullLine[12] = { EMPTY, };
	int _cntLineDeleted = 0;	// count the number of the line deleted
public:
	Background() {}

public:
	void SetBoard(POINT pos, STATE state) { _gameboard[pos.y][pos.x] = state; }
	STATE GetBoard(POINT pos) { return _gameboard[pos.y][pos.x]; }
	bool CheckFullLine();
	void EraseLine(int idx);
};


