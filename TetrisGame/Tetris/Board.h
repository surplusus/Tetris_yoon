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
public:
	Board(Tetromino* tet);
private:
	std::vector<std::vector<bool>>* m_MainBoard;
	std::vector<std::vector<bool>>* m_MiniBoard;
	Block 
	int m_CountLineDeleted = 0;
	Tetromino* m_Tetromino;
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
private:
	
};

