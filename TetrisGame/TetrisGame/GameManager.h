#pragma once
#include "Game.h"

class DrawEngineManager;
class GameManager
{
private:
	static GameManager *Instance;
	GameManager() { game = new Game;}
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
	int gamespeed;
public:		// communicate with TetrisGame
	void Pause();
	void Update();
	int Level();
	void CountTime();
	Game *AccessGame(DrawEngineManager* DM) const { return game; }
	bool IsAllSetUp();
	void SetGameSpeed(const int &_gamespeed) { gamespeed = _gamespeed; }
	const int GetGamespeed() const { return gamespeed; }
public:		// communicate with game member
	void KeyInput(const WPARAM wParam);
	
};

