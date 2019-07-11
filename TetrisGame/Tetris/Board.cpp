#include "stdafx.h"
#include "Board.h"

Board::Board(Tetromino * tet) : m_Tetromino(tet)
{
	//Init();
}

void Board::Init()
{
	m_MainBoard.resize(BoardHeight);
	for (auto &B : m_MainBoard)
	{
		B.assign(BoardWidth, EMPTY);
	}
	m_MiniBoard.resize(BoardHeight);
	for (auto &B : m_MiniBoard)
	{
		B.assign(BoardWidth, EMPTY);
	}
}

void Board::Update()
{

}

void Board::Draw()
{
	Renderer* R = Renderer::GetInstance();
	// draw filled block
	R->DrawBG();
	// draw filled block
	for (auto &B : m_PileBlock)
		R->DrawBlock(B);
}


void Board::NotePile(const std::vector<Block*> tet)
{
	for (auto &t : tet)
	{
		POINT p = t->GetPoint();
		m_MainBoard[p.y][p.x] = FULL;
		Block B = Block(p, Block::BLACK);
		m_PileBlock.push_back(B);
	}
}
