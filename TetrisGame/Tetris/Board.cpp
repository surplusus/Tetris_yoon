#include "stdafx.h"
#include "Board.h"

Board::Board(TargetTet * tet)
{
	m_Target = tet;
}

void Board::Init()
{
	GameProcesser* GP = GameProcesser::GetInstance();
	GP->SetTheirPtrs(this);
	m_MainBoard.resize(BoardHeight);
	for (auto &B : m_MainBoard)
	{
		B.assign(BoardWidth, EMPTY);
	}
}

void Board::Update()
{
	NotePile();
}

void Board::Draw()
{
	Renderer* R = Renderer::GetInstance();
	// draw filled block
	R->DrawBG();
	// draw filled block
	R->SetFuncPtr("main");
	for (auto B : m_PileBlock)
	{
		R->DrawBlock(B);
	}
		
}

void Board::NotePile()
{
	Renderer* R = Renderer::GetInstance();

	for (auto t : m_Target->m_Body)
	{
		POINT p = t->GetPoint();
		m_MainBoard[p.y][p.x] = FULL;
		Block B = Block(p, Block::RED);
		m_PileBlock.push_back(B);
	}
}
