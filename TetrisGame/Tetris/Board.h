#pragma once
#include "Object.h"
#include "Block.h"
#include <vector>
class Tetromino;

class Board : public Object
{
public:
	const int BoardHeight = 15;
	const int BoardWidth = 10;
	const int MiniHegith = 4;
	const int MiniWidth = 3;
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

