#pragma once
#include "Background.h"
#include "Tetromino.h"

class GameManager
{
private:
	static GameManager *Instance;
	GameManager();
	GameManager(GameManager & GM);
	~GameManager();
public:
	static GameManager* GetInstance() {
		if (Instance == nullptr)
			Instance = new GameManager;
		return Instance;
	}
	static void ReleaseInstance() {
		delete Instance;
	}
public:
	bool pause;
	Tetromino *curMino;
	Tetromino *nextMino;
	Background *gameboard;
public:
	bool IsGameOver();
	void Update();
};

