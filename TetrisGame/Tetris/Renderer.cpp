#include "stdafx.h"
#include "Renderer.h"
#include "Game.h"

Renderer* Renderer::Instance = nullptr;

void Renderer::Init(Game * GM)
{
	m_GM = Game::GetInstance();
	hdc = nullptr;
}

void Renderer::Render(HDC & _hdc)
{
	m_GM = Game::GetInstance();

	hdc = &_hdc;
	m_GM->DrawAll();
}

void Renderer::DrawBlock(Block & block)
{
	COLORREF color = block.GetColor();
	HBRUSH hBrush = CreateSolidBrush(color);
	RECT rect = block.GetRECT();
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
