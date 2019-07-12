#include "stdafx.h"
#include "Block.h"

Block::Block(int _x, int _y, COLOR_TYPE _color) : x(_x), y(_y)
{
	pos.x = _x;
	pos.y = _y;
	rect.left = x;
	rect.right = x + BasicPixel;
	rect.top = y;
	rect.bottom = y + BasicPixel;
	SetColor(_color);
}

Block::Block(POINT _pos, COLOR_TYPE _color) : pos(_pos)
{
	x = pos.x;
	y = pos.y;
	rect.left = x;
	rect.right = x + BasicPixel;
	rect.top = y;
	rect.bottom = y + BasicPixel;
	SetColor(_color);
}

Block::Block(RECT _rect, COLOR_TYPE _color) : rect(_rect)
{
	x = rect.left;
	y = rect.top;
	pos.x = x;
	pos.y = y;
	SetColor(_color);
}

void Block::Extend(POINT pos)
{
	rect.right = pos.x;
	rect.bottom = pos.y;
}

void Block::SetColor(COLOR_TYPE _color)
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
	case GRAY:
		color = static_cast<COLORREF>(RGB(204, 204, 204));
	case DARKGRAY:
		color = static_cast<COLORREF>(RGB(104, 104, 104));
	default:
		break;
	}
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

void Block::SetXY(int _x, int _y)
{
	pos = {_x, _y};
	x = _x;
	y = _y;
	rect.left = _x;
	rect.right = _x + BasicPixel;
	rect.top = _y;
	rect.bottom = _y + BasicPixel;
}

Block* Block::operator=(const Block & b1)
{
	this->x = b1.x;	this->y = b1.y;
	this->pos = b1.pos;
	this->rect = b1.rect;
	this->color = b1.color;
	return this;
}