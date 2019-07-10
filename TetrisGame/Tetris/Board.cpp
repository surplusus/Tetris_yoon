#include "stdafx.h"
#include "Board.h"

Board::Board(Tetromino * tet) : m_Tetromino(tet)
{
	m_MainBoard = new std::vector<std::vector<bool>>(BoardHeight, std::vector<bool>(BoardWidth, false));
	m_MiniBoard = new std::vector<std::vector<bool>>(MiniHegith, std::vector<bool>(MiniWidth, false));

}
