#include "stdafx.h"
#include "Tetromino.h"


Tetromino::Tetromino(int x, int y,	TETROMINO_TYPE type) : _type(type)
{
	_center.x = x;	_center.y = y;
	SetTetromino();
	_body.resize(4);
	SetBody(_center);
}

void Tetromino::SetTetromino()
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


bool Tetromino::Rotate()
{	
	_rotation = static_cast<ROTATE_TYPE>((_rotation + 1) % 4);
	VECTORTETRO tmp = _body;

	for (auto &t : _tetromino)		// rotate each blocks in counter-clockwise
	{
		std::swap(t.x, t.y);
		t.x = -t.x;
	}
	
	SetBody(_center);
	
	if (CheckValidPos())
	{
		return true;
	}
	else
	{
		_body = tmp;
		return false;
	}
}

void Tetromino::MoveLeft()
{
	_center.x--;

	if (!CheckValidPos())
		_center.x++;

	SetBody(_center);
}

void Tetromino::MoveDown()
{
	_center.y++;

	if (!CheckValidPos())
		_center.y--;

	SetBody(_center);
}

void Tetromino::MoveRight()
{
	_center.x++;

	if (!CheckValidPos())
		_center.x--;

	SetBody(_center);
}

void Tetromino::GoStrightDown()
{
	while (CheckValidPos())
		MoveDown();
}

bool Tetromino::CheckValidPos()
{
	const int EMPTY = 0;
	for (auto body : _body)
	{	
		if (body.x < 0 || body.x >8)	// boundary of gameboard
			return false;
		if (body.y < 0)				// boundary of gameboard
			return false;
		if (_background->GetBoard(body) != EMPTY)
			return false;
	}
	return true;
}

bool Tetromino::IsBlockOnEnd()
{
	if (_background->GetBoard(_bottom) != Background::EMPTY || _bottom.y <= 0)
	{
		life = false;
		return true;
	}
	return false;
}

void Tetromino::SetBody(POINT center)
{
	// set body based on center
	for (int i = 0; i < 4; ++i)
	{
		_body[i].x = _tetromino[i].x + _center.x;
		_body[i].y = _tetromino[i].y + _center.y;
	}
	// set bottom as the lowest position
	POINT bottom = { 0,0 };
	for (auto t : _body)
		bottom = (bottom.y < t.y) ? t : bottom;
	_bottom = bottom;
}

void Tetromino::Update(KEYVECTOR &key, Background* BG)
{
	SetBackground(BG);
	_center.y++;
	// if press SPACE
	if (key[SPACE] == true)				
		GoStrightDown();

	// if press	ARROW
	if (key[UP] == true)
		Rotate();
	if (key[LEFT] == true)
		MoveLeft();
	if (key[RIGHT] == true)
		MoveRight();
	if (key[DOWN] == true)
		MoveDown();

	
	SetBackground(BG);
	
}

