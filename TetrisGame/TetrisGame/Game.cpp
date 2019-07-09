#include "stdafx.h"
#include "Game.h"
#include "Tetromino.h"

Game::Game()
{
	_gameboard = new Background();
	KEYVECTOR key(5, false);
	_key = key;
	_time = new Time;
	
}


Game::~Game()
{
	delete _curMino;
	delete _nextMino;
	delete _time;
	delete _gameboard;
}

Tetromino * Game::GetTetromino(char CorN)
{
	if (CorN == 'C' || CorN == 'c')
		return _curMino;
	else if (CorN == 'N' || CorN == 'n')
		return _nextMino;
	else
		return nullptr;
}

std::vector<POINT>* Game::GetPileBoard()
{
	std::vector<POINT>* tmp = _gameboard->GetPile();
	return tmp;
}

bool Game::IsAllSetUp()
{
	if (_curMino == nullptr || _nextMino == nullptr ||
		_gameboard == nullptr || _time == nullptr)
		return false;
	else
		return true;
}

void Game::SetKey(WPARAM wParam)
{
	if (wParam == VK_SPACE)
		_key[SPACE] = TRUE;
	if (wParam == VK_LEFT)
		_key[LEFT] = TRUE;
	if (wParam == VK_UP)
		_key[UP] = TRUE;
	if (wParam == VK_RIGHT)
		_key[RIGHT] = TRUE;
	if (wParam == VK_DOWN)
		_key[DOWN] = TRUE;

}

void Game::UpdateCurMino()
{
	while (!IsAllSetUp())
	{
		if (_nextMino == nullptr)
		{
			_nextMino = new Tetromino(1, 1);
		}

		if (_curMino == nullptr)
		{
			POINT center = { 4,0 };
			_curMino = _nextMino;
			_curMino->SetCenter(center);
			_curMino->SetBody(center);
			_nextMino = new Tetromino(1, 1);
		}
	}

	UpdateKey();

	_curMino->Update(_gameboard);

	if (_curMino->IsBlockOnEnd())
	{
		for (auto t : _curMino->GetBody())
		{
			_gameboard->SetBoard(t, Background::FULL);
			_gameboard->SetPile(t);
		}
		delete _curMino;
	}
}

void Game::UpdateTime()
{
	_time->NowTime();
}

void Game::UpdateKey()
{
	// if press SPACE
	if (_key[SPACE] == true)
		_curMino->GoStrightDown();
	// if press	ARROW
	if (_key[UP] == true)
		_curMino->Rotate();
	if (_key[LEFT] == true)
		_curMino->MoveLeft();
	if (_key[RIGHT] == true)
		_curMino->MoveRight();
	if (_key[DOWN] == true)
		_curMino->MoveDown();
	// clear key
	for (int k = 0; k < 5; ++k)
		_key[k] = false;
}

bool Game::GameOver()
{
	POINT deadend1 = { 11,3 };
	POINT deadend2 = { 11,4 };
	
	if (_gameboard->GetBoard(deadend1) || _gameboard->GetBoard(deadend2))
	{
		///////////////// 게임이 끝났을때 처리
		return true;
	}
		

	return false;
}

bool Game::SetPause()
{
	// Can not pause if gameover
	if (GameOver())
		return _pause;

	_pause ^= _pause;
	return _pause;
}