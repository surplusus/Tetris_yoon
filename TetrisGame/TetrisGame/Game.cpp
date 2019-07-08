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
	if (_nextMino == nullptr)
	{
		_nextMino = new Tetromino(1,1);
	}
	
	if (_curMino == nullptr)
	{
		POINT center = { 4,1 };
		_curMino = _nextMino;
		_curMino->SetCenter(center);
		_curMino->SetBody(center);
		_nextMino = new Tetromino(1,1);
	}
	_curMino->Update(_key,_gameboard);

	for (int k = 0; k < 5; ++k)
		_key[k] = false;

	if (_curMino->IsBlockOnEnd())
	{
		for (auto t : _curMino->GetBody())
			_gameboard->SetBoard(t, Background::FULL);
		delete _curMino;
	}
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

void Game::UpdateBackBoard()
{
	////////tetrimino가 끝까지 가면 vectortet 순회하며 full 표시
}

