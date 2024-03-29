#include "stdafx.h"
#include "GameManager.h"

GameManager* GameManager::Instance = nullptr;

void GameManager::Pause()
{
	game->SetPause();
}

void GameManager::Update()
{
	// when pause, stop update
	if (game->GetPause())
		return;

	game->UpdateCurMino();
	
}

void GameManager::KeyInput(const WPARAM wParam)
{
	game->SetKey(wParam);
	game->UpdateCurMino();
}

int GameManager::Level()
{
	if (game == nullptr)
		return 0;
	else
		return game->Level();
}

void GameManager::CountTime()
{
	game->UpdateTime();
}

bool GameManager::IsAllSetUp()
{
	if (game ==nullptr)
		return false;
	if (!game->IsAllSetUp())
		return false;

	return true;
}

