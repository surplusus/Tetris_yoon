#include "stdafx.h"
#include "Tetromino.h"


Tetromino::Tetromino(int x, int y,	TETROMINO_TYPE type) : _type(type)
{
	_center.x = x;	_center.y = y;
	SetBody();
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


bool Tetromino::Rotate()
{	
	_rotation = static_cast<ROTATE_TYPE>((_rotation + 1) % 4);
	VECTORTETRO tmp = _tetromino;

	for (auto body : _tetromino)		// rotate each blocks in counter-clockwise
	{
		std::swap(body.x, body.y);
		body.x = -body.x;
	}

	if (CheckValidPos())
	{
		return true;
	}
	else
	{
		_tetromino = tmp;
		return false;
	}
}

void Tetromino::MoveLeft()
{
	_center.x--;
	if (CheckValidPos())
		return;
	else
		_center.x++;
}

void Tetromino::MoveDown()
{
		_center.y++;
	if (CheckValidPos())
		return;
	else
		_center.y--;
}

void Tetromino::MoveRight()
{
	_center.x++;
	if (CheckValidPos())
		return;
	else
		_center.x--;
}

void Tetromino::GoStrightDown()
{
	while (CheckValidPos())
		MoveDown();
}

bool Tetromino::CheckValidPos()
{
	
	const int EMPTY = 0;
	for (auto body : _tetromino)
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
	if (_background->GetBoard(_center) != 0)
	{
		life = false;
		return true;
	}
	return false;
}

void Tetromino::Update(KEYVECTOR &key, Background* BG)
{
	// if press SPACE
	if (key[SPACE] == TRUE)				
		GoStrightDown();

	// if press	ARROW
	if (key[UP] == TRUE)
		Rotate();
	if (key[LEFT] == TRUE)
		MoveLeft();
	if (key[RIGHT] == TRUE)
		MoveRight();
	if (key[DOWN] == TRUE)
		MoveDown();

	SetBackground(BG);
	_center.y++;
}

