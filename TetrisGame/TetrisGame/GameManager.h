#pragma once
#include "Game.h"

class GameManager
{
private:
	static GameManager *Instance;
	GameManager() { game = new Game; }
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
	Game *game;
	bool _pause = false;
public:		// communicate with TetrisGame
	void Pause();
	void Update();
	int Level();
	void CountTime();
public:		// communicate with game member
	void KeyInput(const WPARAM & wParam);
	
};

