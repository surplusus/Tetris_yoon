#include "stdafx.h"
#include "Renderer.h"
#include "Game.h"

Renderer* Renderer::Instance = nullptr;

void Renderer::Init(Game * GM)
{
	m_GM = Game::GetInstance();
	hdc = nullptr;
	block = nullptr;
}

void Renderer::Render(HDC & _hdc)
{
	m_GM = Game::GetInstance();

	hdc = &_hdc;
	m_GM->DrawAll();
}

void Renderer::DrawBlock(Block& b)
{
	FuncPtr(b);
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
	DrawBlock(mbBB);
	// draw mini background
	POINT miniboardStartPos = { 320, 100 };
	Block mmBB = Block(miniboardStartPos, Block::GRAY);
	POINT miniendPos = { 320 + mmBB.BasicPixel * B->MiniWidth , 100 + mmBB.BasicPixel * B->MiniHegith };
	mmBB.Extend(miniendPos);
	DrawBlock(mmBB);
}

void Renderer::SetFuncPtr(const char * ch)
{
	Renderer* R = GetInstance();
	if (ch == "main")
	{
		FuncPtr = FitInBoard;
		return;
	}
	if (ch == "mini")
	{
		R->FuncPtr = R->FitInMiniBoard;
		return;
	}
	std::cout << "�Լ������� ����" << std::endl;
	return;
}

void Renderer::FitInBoard(Block & b)
{
	block = &b;
	POINT p = block->GetPoint();
	p.x = p.x * Board::BasicPixel + Board::StartPosX;
	p.y = p.y * Board::BasicPixel + Board::StartPosY;
	block->SetPoint(p);
}

void Renderer::FitInMiniBoard(Block & b)
{
	block = &b;
	POINT p = block->GetPoint();
	p.x = p.x * Board::BasicPixel + Board::StartMiniPosX;
	p.y = p.y * Board::BasicPixel + Board::StartMiniPosY;
	block->SetPoint(p);
}
