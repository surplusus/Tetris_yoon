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
	const RECT _rectGameBoard = { 50,50,50 + basicPixel * 8, 50 + basicPixel * 12 };
	HDC _hdc;
	HDC _memDC[3];	//internal temporary memory Handle Device Context
	HWND _hwnd;
	RECT _rect;		// internal temporary rect variable
	int _x, _y;		// internal temporary coordinate variable
	POINT _pos;		// internal temporary POINT variable
	POINT _boardStartPos = { 50,50 };	// board start from here
	int _boardWidth = 200;	// board width
	int _boardHeight = 300;	// board heigth
	BLENDFUNCTION _blendfunction;
public:
	DrawEngine(const HWND & hwnd, const HDC & hdc,  int width = 10, int height = 20) :
		_hdc(hdc), _hwnd(hwnd), _boardWidth(width), _boardHeight(height) {
		_blendfunction.AlphaFormat = AC_SRC_ALPHA;
		_blendfunction.BlendFlags = 0;
		_blendfunction.SourceConstantAlpha = 150;
		_blendfunction.BlendOp = AC_SRC_OVER;
	}
public:
	void Render(Game* G);	// reflect all the draw function 
	void DrawBlock(POINT pos, COLORREF color);	// draw basic block which makes tetromino
	void DrawTetromino(const Tetromino& tet);
	void DrawGameBoard(RECT &GameBoard);	// draw interface of tetris which is used in gameplay
	void DrawPause();
	void DrawScore(int &x, int &y);
	void DrawSpeed(int &x, int &y);
	void DrawTime(int &x, int &y);
	const COLORREF Color(const Tetromino::TETROMINO_TYPE type);
	void SetHDC(HDC & hdc) { _hdc = hdc; }
	POINT& SetDrawPoint(POINT pos);
	POINT& SetDrawPoint(int x, int y);
	RECT &SetDrawRect(POINT p1,POINT p2);
};

