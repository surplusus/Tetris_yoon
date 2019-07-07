#include "stdafx.h"

DrawEngineManager* DrawEngineManager::Instance = nullptr;

void DrawEngineManager::Render(HDC & hdc)
{
	Game* G = AccessGame();
	DE->SetHDC(hdc);
	DE->Render(G);
}

Game* DrawEngineManager::AccessGame()
{
	GameManager* GM = GameManager::GetInstance();
	if (GM->AccessGame(this) == nullptr)
		return nullgame;
	else
		return GM->AccessGame(this);
}
