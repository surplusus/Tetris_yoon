#include "stdafx.h"
#pragma comment (lib, "Msimg32.lib")
#include <vector>

void DrawEngine::Render(Game* G)
{
	// draw backboard
	_pos = SetDrawPoint(_boardStartPos);
	_rect = _rectGameBoard;
	DrawGameBoard(_rect);
	// draw nextblockboard
	POINT p1 = SetDrawPoint(_nextboardStartPos);
	POINT p2 = SetDrawPoint(p1.x+basicPixel*3, p1.y + basicPixel * 3);
	RECT nextBlockBoard = SetDrawRect(p1, p2);
	DrawGameBoard(nextBlockBoard);
	
	// draw nextmino
	 Tetromino* tet = G->GetTetromino('N');
	if (tet != nullptr)
	{
		DrawTetromino(*tet, 'N');
	}
	
	tet = G->GetTetromino('C');
	if (tet != nullptr)
	{
		// draw curmino
		DrawTetromino(*tet, 'C');
		// draw predict Block
		DrawTetromino(*tet, 'P');
	}
	// draw piled block

	for (auto B : *(G->GetPileBoard()))
		DrawBlock(B, RGB(55, 55, 55));
}

void DrawEngine::DrawBlock(POINT pos, COLORREF color)
{
	_memDC[0] = _hdc;
	BitBlt(_memDC[2], 0, 0, 800, 600, _memDC[0], 0, 0, SRCCOPY);

	HBRUSH hBrush = CreateSolidBrush(color);
	_rect.left = pos.x;
	_rect.top = pos.y;
	_rect.right = pos.x + basicPixel;
	_rect.bottom = pos.y + basicPixel;

	FillRect(_hdc, &_rect, hBrush);
	DeleteObject(hBrush);

	// apply padding & alpha at Rect
	HDC alphaDC = CreateCompatibleDC(_memDC[2]); // copy info of hdc to alphaDC
	HBITMAP tmpBit = CreateCompatibleBitmap(_memDC[2], 800, 600);  // copy hdc to hbitmap
	HBITMAP oldBit = (HBITMAP)SelectObject(alphaDC, tmpBit);
	BitBlt(alphaDC, 0, 0, 800, 600, _memDC[2], 0, 0, SRCCOPY);  // copy info of screen to alphaDC
	int padding = 7;
	int alphaX = pos.x + padding;	int alphaY = pos.y + padding;
	int alphaSize = basicPixel - padding * 2;

	TransparentBlt(alphaDC, alphaX, alphaY, alphaSize, alphaSize,
		_memDC[1], alphaX, alphaY, alphaSize, alphaSize, color);
	AlphaBlend(_memDC[2], alphaX, alphaY, alphaSize, alphaSize,
		alphaDC, alphaX, alphaY, alphaSize, alphaSize, _blendfunction);

	DeleteObject(tmpBit);

}

void DrawEngine::DrawTetromino(const Tetromino& tet, char ch)
{
	POINT cen = tet.GetCenter();	// make _tetromino[1] as _center
	// create hbrush based on tetromino type;
	COLORREF color = (COLORREF)(Color(tet.GetType()));
	COLORREF gray = (COLORREF)(RGB(230, 230, 230));

	if (ch == 'N' || ch == 'n')
	{
		for (auto t : tet.GetBody())
		{
			t.x = _nextboardStartPos.x + t.x * basicPixel;
			t.y = _nextboardStartPos.y + t.y * basicPixel;
			DrawBlock(t, color);
		}
	}
	else if (ch == 'C' || ch == 'c')
	{
		for (auto t : tet.GetBody())
		{
			t.x = _boardStartPos.x + t.x * basicPixel;
			t.y = _boardStartPos.y + t.y * basicPixel;
			DrawBlock(t, color);
		}
	}
	else if (ch == 'P' || ch == 'p')
	{
		for (auto t : tet.GetPredict())
		{
			t.x = _boardStartPos.x + t.x * basicPixel;
			t.y = _boardStartPos.y + t.y * basicPixel;
			DrawBlock(t, gray);
		}
	}
}

void DrawEngine::DrawGameBoard(RECT &GameBoard)
{
	// draw a gray area on the board
	HBRUSH hBrush = CreateSolidBrush(RGB(100, 100, 100));
	FillRect(_hdc, &GameBoard, hBrush);
	//oldBrush = (HBRUSH)SelectObject(_hdc, hBrush);
	DeleteObject(hBrush);
}

void DrawEngine::DrawPause()
{
	// center of gameboard
	_x = _boardStartPos.x + (_boardWidth / 2);
	_y = _boardStartPos.y + (_boardHeight / 2);	
	DrawScore(_x, _y);
	_y = _boardStartPos.y + (_boardHeight / 2) + 20;
	DrawSpeed(_x, _y);
}

RECT &DrawEngine::SetDrawRect(POINT p1, POINT p2)
{
	_rect.left = p1.x;	// origin coornate
	_rect.top = p1.y;		// origin coornate
	_rect.right = p2.x;	// new pos
	_rect.bottom = p2.y;	// new pos
	return _rect;
}

void DrawEngine::DrawScore(int & x, int & y)
{
	TCHAR szBuffer[20];
	DrawEngineManager* DE = DrawEngineManager::GetInstance();
	int score = DE->AccessGame()->GetScore();
	int text = wsprintf(szBuffer, TEXT("Score: %6d"),score);
	SetBkMode(_hdc, OPAQUE);
	TextOut(_hdc, x, y, szBuffer, text);
	SetBkMode(_hdc, TRANSPARENT);
}

void DrawEngine::DrawSpeed(int & x, int & y)
{
	TCHAR szBuffer[20];
	GameManager* GM = GameManager::GetInstance();
	int text = wsprintf(szBuffer, TEXT("Speed: %6d"), GM->GetGamespeed());
	SetBkMode(_hdc, OPAQUE);
	TextOut(_hdc, x, y, szBuffer, text);
	SetBkMode(_hdc, TRANSPARENT);
}

void DrawEngine::DrawTime(int & x, int & y)
{
	TCHAR szBuffer[20];
	DrawEngineManager* DE = DrawEngineManager::GetInstance();
	int time = DE->AccessGame()->GetTime();
	int text = wsprintf(szBuffer, TEXT("Score: %6d"), time);
	SetBkMode(_hdc, OPAQUE);
	TextOut(_hdc, x, y, szBuffer, text);
	SetBkMode(_hdc, TRANSPARENT);
}

const COLORREF DrawEngine::Color(const Tetromino::TETROMINO_TYPE type)
{
	switch (type)
	{
	case Tetromino::TETROMINO_I:
		return static_cast<COLORREF>(RGB(77, 100, 255));
	case Tetromino::TETROMINO_J:
		return static_cast<COLORREF>(RGB(70, 232, 161));
	case Tetromino::TETROMINO_L:
		return static_cast<COLORREF>(RGB(255, 254, 90));
	case Tetromino::TETROMINO_O:
		return static_cast<COLORREF>(RGB(232, 147, 70));
	case Tetromino::TETROMINO_S:
		return static_cast<COLORREF>(RGB(255, 87, 219));
	case Tetromino::TETROMINO_T:
		return static_cast<COLORREF>(RGB(143, 232, 70));
	case Tetromino::TETROMINO_Z:
		return static_cast<COLORREF>(RGB(255, 249, 236));
	}
}

POINT& DrawEngine::SetDrawPoint(POINT pos)
{
	_pos = pos;
	_x = pos.x;
	_y = pos.y;
	return pos;
}

POINT& DrawEngine::SetDrawPoint(int x, int y)
{
	_x = x;
	_y = y;
	_pos.x = x;
	_pos.y = y;
	return _pos;
}
