#include "stdafx.h"
#include "Tetromino.h"


Tetromino::Tetromino(int x, int y,	TETROMINO_TYPE type) : _type(type)
{
	_center.x = x;	_center.y = y;
	SetTetromino();
	_body.resize(4);
	SetBody(_center);
	_predict.resize(4);
	SetPredict();
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

	SetPredict();
	VECTORTETRO tmpbody = GetBody();
	VECTORTETRO tmppredict = GetPredict();
	for (int i = 0; i < 4; ++i)
	{
		if (tmpbody[i].x == tmppredict[i].x && tmpbody[i].y == tmppredict[i].y)
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
	
}

void Tetromino::SetPredict()
{
	if (_background != nullptr)
	{
		int i, j;
		int gap = boardHeight-1;
		POINT tmp;
		for (i = 0; i < 4; ++i)
		{
			_predict[i].x = tmp.x = _body[i].x;
			for (j = 0; j < boardHeight; ++j)
			{
				tmp.y = j;
				if (_background->GetBoard(tmp) != Background::EMPTY)
					break;
			}
			gap = gap < (_body[i].y - tmp.y);
			_predict[i] = tmp;
		}
	}
}

void Tetromino::Update(Background* BG)
{
	SetBackground(BG);

	if (CheckValidPos())
		MoveDown();
	
	SetBackground(BG);
	
}

