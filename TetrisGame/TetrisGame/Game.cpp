#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	KEYVECTOR key(5, FALSE);
	_key = key;
	_curMino = new Tetromino();
	_nextMino = new Tetromino();
	_time = new Time;
	_gameboard = new Background();
}


Game::~Game()
{
	delete _curMino;
	delete _nextMino;
	delete _time;
	delete _gameboard;
}

void Game::SetKey(const WPARAM & wParam)
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
	_curMino->KeyInput(_key);
	for (int k = 0; k < 5; ++k)
		_key[k] = FALSE;
}

void Game::UpdateCurMino()
{
	_curMino->GetBoard(*_gameboard);
	_curMino->Update();
}

void Game::UpdateTime()
{
	_time->NowTime();
}

bool Game::Pause()
{
	// Can not pause if gameover
	if (GameOver())
		return _pause;

	_pause ^= _pause;
	return _pause;
}

