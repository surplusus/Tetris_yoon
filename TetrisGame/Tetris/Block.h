#pragma once
class Block
{
private:
	const int BasicPixel = 25;
	int x;
	int y;
	POINT pos;
	RECT rect;
	COLORREF color;
public:
	enum COLOR_TYPE	{
		WHITE=0, BLACK, GRAY, BLUE, MINT, 
		LEMON, ORANGE,PINK,GREEN, RED
	};
	Block(int _x, int _y, COLOR_TYPE _color);
	Block(POINT _pos, COLOR_TYPE _color);
	Block(RECT _rect, COLOR_TYPE _color);
	~Block() {}
private:
	void Color(COLOR_TYPE _color);
public:
	POINT GetPoint() { return pos; }
	RECT GetRECT() { return rect; }
	COLORREF GetColor() { return color; }
	void SetColor(COLOR_TYPE _color) { Color(_color); }
	void SetPoint(POINT p);
};

