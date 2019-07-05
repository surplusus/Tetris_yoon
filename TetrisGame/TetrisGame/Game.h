#pragma once
#include "Background.h"
#include "Tetromino.h"
#include "Time.h"
#include <vector>

class Game
{
private:
	using KEYVECTOR = std::vector<bool>;
	enum KEY {SPACE, LEFT, UP,RIGHT,DOWN};
public:
	Game();
	~Game();
private:
	bool _pause = false;
	bool _gameover;
	Tetromino *_curMino;
	Tetromino *_nextMino;
	Background *_gameboard;
	int _score;
	Time *_time;
	int _level;
	KEYVECTOR _key;
public:
	void SetKey(const WPARAM & wParam);
	int ShowTime();
	int Level() { return _level; }
	void CreateNextTetromino();
	void UpdateCurMino();
	void 
	bool GameOver();
	bool Pause();
};

