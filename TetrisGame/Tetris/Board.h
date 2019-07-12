#pragma once
#include "Object.h"
#include "Block.h"
#include <vector>
class Tetromino;
class TargetTet;

class Board : public Object
{
public:
	static const int BoardHeight = 15;
	static const int BoardWidth = 10;
	static const int MiniHegith = 3;
	static const int MiniWidth = 4;
	static const int StartPosX = 50;
	static const int StartPosY = 50;
	static const int StartMiniPosX = 320;
	static const int StartMiniPosY = 100;
	static const int BasicPixel = 25;
	POINT StartPos = { 50,50 };
	enum BOARD_TYPE {EMPTY = 0, FULL = 1};
public:
	Board(TargetTet* tet);
	virtual ~Board() {}
private:
	std::vector<std::vector<bool>> m_MainBoard;
	std::vector<Block> m_PileBlock;
	int m_CountLineDeleted = 0;
	TargetTet* m_Target;	// internal temporary variable
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
public:
	const bool GetBoardType(const POINT& pos) 
	{ return m_MainBoard[pos.y][pos.x]; }
private:
	void NotePile();
};

