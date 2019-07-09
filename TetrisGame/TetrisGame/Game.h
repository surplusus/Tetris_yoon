#pragma once
#include "Background.h"
#include "Tetromino.h"
#include "Time.h"
#include <vector>

class Game
{
private:
	using KEYVECTOR = std::vector<bool>;
	enum KEY_TYPE {SPACE=0, LEFT, UP,RIGHT,DOWN};
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
private:
	//void CreateNextTetromino();

public:		// Getter
	Tetromino* GetTetromino(char CorN);
	int GetScore() { return _score; }
	int GetTime() { return _time->NowTime(); }
	bool GetPause() { return _pause; }
	std::vector<POINT>* GetPileBoard();
public:
	bool IsAllSetUp();
	void SetKey(WPARAM wParam);
	int Level() { return _level; }
	bool GameOver();
	bool SetPause();
public:		//update()
	void UpdateCurMino();
	void UpdateTime();
	void UpdateKey();
};

