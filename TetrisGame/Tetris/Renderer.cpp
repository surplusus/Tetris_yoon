#include "stdafx.h"
#include "Renderer.h"
#include "Game.h"

Renderer* Renderer::Instance = nullptr;

void Renderer::Init(GameProcesser * GM)
{
	m_GM = GameProcesser::GetInstance();
	hdc = nullptr;
	block = new Block();
}

void Renderer::Render(HDC & _hdc)
{
	m_GM = GameProcesser::GetInstance();
	hdc = &_hdc;
	m_GM->DrawAll();
}

void Renderer::DrawBlock(Block& b)
{
	(this->*FuncPtr)(b);
	COLORREF color = block->GetColor();
	HBRUSH hBrush = CreateSolidBrush(color);
	RECT rect = block->GetRECT();
	FillRect(*hdc, &rect, hBrush);
	DeleteObject(hBrush);
}

void Renderer::DrawBG()
{
	const Board* B = m_GM->GetBoard();
	// draw mainboard background
	Block mbBB = Block(B->StartPos, Block::GRAY);
	POINT mainendPos = { 50 + mbBB.BasicPixel * B->BoardWidth, 50 + mbBB.BasicPixel * B->BoardHeight };
	mbBB.Extend(mainendPos);
	SetFuncPtr("back");
	DrawBlock(mbBB);
	// draw mini background
	POINT miniboardStartPos = { 320, 100 };
	Block mmBB = Block(miniboardStartPos, Block::GRAY);
	POINT miniendPos = { 320 + mmBB.BasicPixel * B->MiniWidth , 100 + mmBB.BasicPixel * B->MiniHegith };
	mmBB.Extend(miniendPos);
	SetFuncPtr("back");
	DrawBlock(mmBB);
}

void Renderer::SetFuncPtr(const char * ch)
{
	
	if (ch == "main")
	{
		FuncPtr = &Renderer::FitInBoard;
		return;
	}
	if (ch == "mini")
	{
		FuncPtr = &Renderer::FitInMiniBoard;
		return;
	}
	if (ch == "back")
	{
		FuncPtr = &Renderer::FitInBackBoard;
		return;
	}
	std::cout << "함수포인터 에러" << std::endl;
	return;
}

void Renderer::FitInBoard(const Block & b)
{
	*block = b;
	POINT p = block->GetPoint();
	p.x = p.x * Board::BasicPixel + Board::StartPosX;
	p.y = p.y * Board::BasicPixel + Board::StartPosY;
	block->SetPoint(p);
}

void Renderer::FitInMiniBoard(const Block & b)
{
	*block = b;
	POINT p = block->GetPoint();
	p.x = p.x * Board::BasicPixel + Board::StartMiniPosX;
	p.y = p.y * Board::BasicPixel + Board::StartMiniPosY;
	block->SetPoint(p);
}

void Renderer::FitInBackBoard(const Block & b)
{
	*block = b;
}
