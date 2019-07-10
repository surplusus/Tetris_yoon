#pragma once
#include "Board.h"
#include "Tetromino.h"
#include "Renderer.h"
#include "Key.h"

class Game
{
public:
	Game();
	~Game();
private:
	Key* m_Key;
	Tetromino* m_CurTet;
	Tetromino* m_NextTet;
	TargetTet* m_Target;
	Board* m_GameBoard;
public:		// Interface
	void InitAll();
	void Update();
	void InputKey(const WPARAM& wParam);

private:	// Mediator
	
	//void TetBodyToBoard(Object* ob);
};

