#pragma once
#include "Game.h"

class GameManager
{
private:
	static GameManager *Instance;
	GameManager() {}
	GameManager(GameManager & GM) {}
	~GameManager() {delete game;}
public:
	static GameManager* GetInstance() {
		if (Instance == nullptr)
			Instance = new GameManager;
		return Instance;
	}
	static void ReleaseInstance() {
		delete Instance;
	}
private:
	DrawEngine *DE;
	Game *game;
	bool _pause = false;
public:
	void Init(DrawEngine &DEorigin);
	void Pause();
	void Update();
	void KeyInput(const WPARAM & wParam);
	int Level();
};

