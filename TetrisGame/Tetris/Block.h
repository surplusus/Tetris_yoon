#pragma once
class Block
{
private:
	int x;
	int y;
	POINT pos;
	RECT rect;
	COLORREF color;
public:
	const int BasicPixel = 25;
	enum COLOR_TYPE	{
		WHITE=0, BLACK, GRAY, BLUE, MINT, 
		LEMON, ORANGE,PINK,GREEN, RED
	};
	Block() : x(0), y(0), pos(POINT()), rect(RECT()), color(COLORREF()) {}
	Block(int _x, int _y, COLOR_TYPE _color);
	Block(POINT _pos, COLOR_TYPE _color);
	Block(RECT _rect, COLOR_TYPE _color);
	~Block() {}
private:
	void Color(COLOR_TYPE _color);

public:
	const POINT& GetPoint() const { return pos; }
	const RECT& GetRECT() const { return rect; }
	const COLORREF& GetColor() const { return color; }
	void Extend(POINT pos);
	void SetColor(COLOR_TYPE _color) { Color(_color); }
	void SetPoint(POINT p);
	Block operator=(Block& b1);
};

