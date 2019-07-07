#include "stdafx.h"
#include "Game.h"
#include "Tetromino.h"

Game::Game()
{
	KEYVECTOR key(5, FALSE);
	_gameboard = new Background();
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
	if (_nextMino == nullptr)
	{
		_nextMino = new Tetromino;
	}
	
	if (_curMino == nullptr)
	{
		_curMino = _nextMino;
		_nextMino = new Tetromino;
	}
	_curMino->Update(_key,_gameboard);

	for (int k = 0; k < 5; ++k)
		_key[k] = FALSE;

	if (_curMino->IsBlockOnEnd())
		delete _curMino;
}

void Game::UpdateTime()
{
	_time->NowTime();
}

bool Game::GameOver()
{
	POINT deadend1 = { 11,3 };
	POINT deadend2 = { 11,4 };
	
	if (_gameboard->GetBoard(deadend1) || _gameboard->GetBoard(deadend2))
	{
		///////////////// ������ �������� ó��
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

void Game::UpdateBackBoard()
{
	////////tetrimino�� ������ ���� vectortet ��ȸ�ϸ� full ǥ��
}

