#include "stdafx.h"
#include "Block.h"

Block::Block(int _x, int _y, COLOR_TYPE _color) : x(_x), y(_y)
{
	pos = { x,y };
	rect.left = x;
	rect.right = x + BasicPixel;
	rect.top = y;
	rect.bottom = y + BasicPixel;
	Color(_color);
}

Block::Block(POINT _pos, COLOR_TYPE _color) : pos(_pos)
{
	x = pos.x;
	y = pos.y;
	rect.left = x;
	rect.right = x + BasicPixel;
	rect.top = y;
	rect.bottom = y + BasicPixel;
	Color(_color);
}

Block::Block(RECT _rect, COLOR_TYPE _color) : rect(_rect)
{
	x = rect.left;
	y = rect.top;
	pos = { x,y };
	Color(_color);
}

void Block::Extend(POINT pos)
{
	rect.right = pos.x;
	rect.bottom = pos.y;
}

void Block::SetPoint(POINT p)
{
	pos = p;
	x = p.x;
	y = p.y;
	rect.left = x;
	rect.right = x + BasicPixel;
	rect.top = y;
	rect.bottom = y + BasicPixel;
}

Block Block::operator=(Block & b1)
{
	Block b;
	b.x = b1.x;	b.y = b1.y;
	b.pos = b1.pos;
	b.rect = b1.rect;
	b.color = b.color;
	return b;
}

void Block::Color(COLOR_TYPE _color)
{
	switch (_color)
	{
	case WHITE:
		color = static_cast<COLORREF>(RGB(255, 249, 236));
		break;
	case BLACK:
		color = static_cast<COLORREF>(RGB(20, 20, 20));
		break;
	case BLUE:
		color = static_cast<COLORREF>(RGB(77, 100, 255));
		break;
	case MINT:
		color = static_cast<COLORREF>(RGB(70, 232, 161));
		break;
	case LEMON:
		color = static_cast<COLORREF>(RGB(255, 254, 90));
		break;
	case ORANGE:
		color = static_cast<COLORREF>(RGB(232, 147, 70));
		break;
	case PINK:
		color = static_cast<COLORREF>(RGB(255, 87, 219));
		break;
	case GREEN:
		color = static_cast<COLORREF>(RGB(143, 232, 70));
		break;
	case RED:
		color = static_cast<COLORREF>(RGB(204, 51, 0));
		break;
	default:
		break;
	}
}
