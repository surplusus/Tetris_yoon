#pragma once

typedef struct _BLENDFUNCTION {
	BYTE blendOp = AC_SRC_OVER;
	BYTE blendFlags = 0;
	BYTE SourceconstantAlpha = 150;
	BYTE AlphaFormat = 0;
}BLENDFUNCTION, *PBLENDFUNCTION;

class DrawEngine
{
private:
	const int basicPixel = 25;
	HDC _hdc;
	HDC _memDC[3];
	HWND _hwnd;
	RECT _rect;	 // internal temporary rect variable
	int _maxwidth;
	int _maxheight;
	BLENDFUNCTION _blendfunction;
public:
	DrawEngine(HDC hdc, HWND hwnd, int width = 10, int height = 20);
	~DrawEngine();
	void DrawBlock(POINT pos, COLORREF color);	// draw basic block which makes tetromino

};

