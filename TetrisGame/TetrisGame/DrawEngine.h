#pragma once

//typedef struct _BLENDFUNCTION {
//	BYTE BlendOp = AC_SRC_OVER;
//	BYTE BlendFlags = 0;
//	BYTE SourceConstantAlpha = 150;
//	BYTE AlphaFormat = AC_SRC_ALPHA;
//} BLENDFUNCTION, *PBLENDFUNCTION;

class DrawEngine
{
private:
	const int basicPixel = 25;
	HDC _hdc;
	HDC _memDC[3];	//internal temporary memory Handle Device Context
	HWND _hwnd;
	RECT _rect;	 // internal temporary rect variable
	int _maxwidth;
	int _maxheight;
	BLENDFUNCTION _blendfunction;
public:
	DrawEngine(const HWND & hwnd, const HDC & hdc,  int width = 10, int height = 20) :
		_hdc(hdc), _hwnd(hwnd), _maxwidth(width), _maxheight(height) {
		_blendfunction.AlphaFormat = AC_SRC_ALPHA;
		_blendfunction.BlendFlags = 0;
		_blendfunction.SourceConstantAlpha = 150;
		_blendfunction.BlendOp = AC_SRC_OVER;
	}
public:
	void Render();	// reflect all the draw function 
	void DrawBlock(POINT pos, COLORREF color);	// draw basic block which makes tetromino
	void DrawGameBoard(RECT GameBoard);	// draw interface of tetris which is used in gameplay
	void DrawPause();
	void DrawScore();
	void DrawSpeed();
	void DrawTime()
};

