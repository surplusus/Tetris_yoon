#include "stdafx.h"
#include "Tetromino.h"

COLORREF Tetromino::Color()
{
	switch (_type)
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

void Tetromino::SetBody()
{
	_tetromino.resize(4);
	switch (_type)
	{
	case Tetromino::TETROMINO_I:
		_tetromino[0].x = -1;	_tetromino[0].y = 0;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = 1;	_tetromino[2].y = 0;
		_tetromino[3].x = 2;	_tetromino[3].y = 0;
		break;
	case Tetromino::TETROMINO_J:
		_tetromino[0].x = 0;	_tetromino[0].y = 1;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = 1;	_tetromino[2].y = 0;
		_tetromino[3].x = 2;	_tetromino[3].y = 0;
		break;
	case Tetromino::TETROMINO_L:
		_tetromino[0].x = 0;	_tetromino[0].y = -1;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = 1;	_tetromino[2].y = 0;
		_tetromino[3].x = 2;	_tetromino[3].y = 0;
		break;
	case Tetromino::TETROMINO_O:
		_tetromino[0].x = 1;	_tetromino[0].y = 0;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = 0;	_tetromino[2].y = 1;
		_tetromino[3].x = 1;	_tetromino[3].y = 1;
		break;
	case Tetromino::TETROMINO_S:
		_tetromino[0].x = -1;	_tetromino[0].y = 0;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = 0;	_tetromino[2].y = 1;
		_tetromino[3].x = 1;	_tetromino[3].y = 1;
		break;
	case Tetromino::TETROMINO_T:
		_tetromino[0].x = 1;	_tetromino[0].y = 0;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = -1;	_tetromino[2].y = 0;
		_tetromino[3].x = 0;	_tetromino[3].y = 1;
		break;
	case Tetromino::TETROMINO_Z:
		_tetromino[0].x = 0;	_tetromino[0].y = 1;
		_tetromino[1].x = 0;	_tetromino[1].y = 0;
		_tetromino[2].x = -1;	_tetromino[2].y = -1;
		_tetromino[3].x = 1;	_tetromino[3].y = 0;
		break;
	}

}

Tetromino::Tetromino(TETROMINO_TYPE type, int x =4, int y=1 ) : _type(type)
{
	_center.x = x;	_center.y = y;
	SetBody();

}

bool Tetromino::Rotate()
{	// not yet
	_rotation = static_cast<ROTATE_TYPE>((_rotation + 1) % 4);
	VECTORTETRO tmp = _tetromino;

	for (auto body : _tetromino)		// rotate each blocks in counter-clockwise
	{
		std::swap(body.x, body.y); 
		body.x = -body.x;
	}
	if (checkValidPos())
	{
		return true;
	}
	else
	{
		_tetromino = tmp;
		return false;
	}
}

void Tetromino::Move()
{
	_center.y++;
}

void Tetromino::GoDown()
{
	while (checkValidPos())
		Move();
}

bool Tetromino::checkValidPos()
{
	const int EMPTY = 0;
	for (auto body : _tetromino)
	{	
		if (body.x < 0 || body.x >8)	// boundary of gameboard
			return false;
		if (body.y < 0)				// boundary of gameboard
			return false;
		if (GameManager::GetInstance()->gameboard->GetBoard(body) != EMPTY)
			return false;
	}
	return true;
}
