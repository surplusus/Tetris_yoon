#pragma once

class Background
{
	enum STATE{EMPTY, FILL};
	enum va{er,df};
	int aa[7] = { er,df,EMPTY,FILL };
private:
	STATE _gameboard[10][20] = { EMPTY, };
	int _cntLineDeleted = 0;
public:
	Background();
public:
	const int GetBoard(POINT pos) const { return _gameboard[pos.y][pos.x]; }
	void SetBoard(POINT pos, STATE state) { _gameboard[pos.y][pos.x] = state; }
	bool CheckFullLine(POINT curPos);
	
};


