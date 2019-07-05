#include "stdafx.h"
#include "GameManager.h"

GameManager* GameManager::Instance = nullptr;

void GameManager::Init(DrawEngine &DEorigin)
{

	//DE = &DEorigin;
	game = new Game;
}

void GameManager::Pause()
{
	_pause = game->Pause();
	if (_pause)
	{
		game->Pause();
		DE->DrawPause();
	}
	else
	{

	}
}

void GameManager::Update()
{
	// when pause, stop update
	if (_pause)
		return;

	game->UpdateCurMino();
}

void GameManager::KeyInput(const WPARAM & wParam)
{
	game->SetKey(wParam);
	game->UpdateCurMino();
}

int GameManager::Level()
{
	return game->Level();
}

