#pragma once
#include "Object.h"
#include "Block.h"
#include <vector>
class Tetromino;

class Board : public Object
{
public:
	static const int BoardHeight = 15;
	static const int BoardWidth = 10;
	static const int MiniHegith = 4;
	static const int MiniWidth = 3;
	static const int StartPosX = 50;
	static const int StartPosY = 50;
	static const int StartMiniPosX = 320;
	static const int StartMiniPosY = 100;
	static const int BasicPixel = 25;
	POINT StartPos = { 50,50 };
	enum BOARD_TYPE {EMPTY = 0, FULL = 1};
public:
	Board(Tetromino* tet);
	virtual ~Board() {}
private:
	std::vector<std::vector<bool>> m_MainBoard;
	std::vector<std::vector<bool>> m_MiniBoard;
	std::vector<Block> m_PileBlock;
	int m_CountLineDeleted = 0;
	std::vector<POINT> m_CheckPos; // internal temporary variable
	Tetromino* m_Tetromino;
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	void NotePile(const std::vector<Block*> tet);
	const bool& GetBoardType(const POINT& pos) { return m_MainBoard[pos.y][pos.y]; }
private:
	
};

