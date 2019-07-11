#pragma once
#include "Board.h"
#include "Tetromino.h"
#include "Renderer.h"
#include "Key.h"

class Game
{
private:
	Game();
	Game(Game& g);
	~Game();
	static Game* Instance;
public:
	static Game* GetInstance() {
		if (!Instance)
			Instance = new Game;
		return Instance;}
	static void ReleaseInstance() {
		delete Instance;}
private:
	Key* m_Key;
	UseTet* m_CurTet;
	UseTet* m_NextTet;
	TargetTet* m_Target;
	Board* m_GameBoard;
public:		// Interface
	void InitAll();
	void UpdateAll();
	void InputKey(const WPARAM& wParam);
	void DrawAll();
	const Board* GetBoard() const { return m_GameBoard; }
};

