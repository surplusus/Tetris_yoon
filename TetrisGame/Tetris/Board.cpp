#include "stdafx.h"
#include "Board.h"

Board::Board(Tetromino * tet) : m_Tetromino(tet)
{
	m_MainBoard = new std::vector<std::vector<bool>>(BoardHeight, std::vector<bool>(BoardWidth, false));
	m_MiniBoard = new std::vector<std::vector<bool>>(MiniHegith, std::vector<bool>(MiniWidth, false));

}

void Board::Update()
{
	for (auto p : m_CheckPos)
	{
		m_MainBoard[p.y][p.x] = FULL;
	}
	m_CheckPos.clear();
}

void Board::NotePile(const std::vector<Block*> tet)
{
	for (auto t : tet)
	{
		POINT p = t->GetPoint();
		m_CheckPos.push_back(p);
	}
}
