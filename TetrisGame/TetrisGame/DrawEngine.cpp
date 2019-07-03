#include "stdafx.h"
#include "DrawEngine.h"


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
		alphaDC,alphaX, alphaY, alphaSize, alphaSize, _blendfunction);
}
