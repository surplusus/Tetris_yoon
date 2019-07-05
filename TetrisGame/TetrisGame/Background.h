#pragma once

class Background
{
	const int basicPixel = 25;
	enum STATE{EMPTY, FILL};
private:
	STATE _gameboard[12][8] = { EMPTY, };
	int _cntLineDeleted = 0;	// count the number of the line deleted
public:
	Background();
public:
	RECT _rectGameBoard = { 50,50,basicPixel * 8, basicPixel * 12 };
	const int GetBoard(POINT pos) const { return _gameboard[pos.y][pos.x]; }
	void SetBoard(POINT pos, STATE state) { _gameboard[pos.y][pos.x] = state; }
	bool CheckFullLine(POINT curPos);
	
};


