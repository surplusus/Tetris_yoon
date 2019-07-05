#pragma once
#include "Background.h"
#include "Tetromino.h"
#include "Time.h"
#include <vector>

class Game
{
private:
	using KEYVECTOR = std::vector<bool>;
	enum KEY_TYPE {SPACE, LEFT, UP,RIGHT,DOWN};
public:
	Game();
	~Game();
private:
	bool _pause = false;
	bool _gameover;
	Tetromino *_curMino;
	Tetromino *_nextMino;
	Background *_gameboard;
	int _score = 0;
	Time *_time;
	int _level = 1;
	KEYVECTOR _key;
public:
	void SetKey(const WPARAM & wParam);
	int Level() { return _level; }
	void CreateNextTetromino();
	void UpdateCurMino();
	void UpdateTime();
	bool GameOver();
	bool Pause();
};

