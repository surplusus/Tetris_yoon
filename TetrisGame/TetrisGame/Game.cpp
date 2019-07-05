#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	KEYVECTOR key(5, FALSE);
	_key = key;
}


Game::~Game()
{
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
}

int Game::ShowTime()
{
	return _time->NowTime();
}

void Game::UpdateCurMino()
{
}

bool Game::Pause()
{
	// Can not pause if gameover
	if (GameOver())
		return _pause;

	_pause ^= _pause;
	return _pause;
}

