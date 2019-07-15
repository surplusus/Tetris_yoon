#pragma once
#include "Board.h"
#include "Tetromino.h"
#include "Renderer.h"
#include "Key.h"

class GameProcesser
{
private:
	GameProcesser();
	GameProcesser(GameProcesser& g);
	~GameProcesser();
	static GameProcesser* Instance;
public:
	static GameProcesser* GetInstance() {
		if (!Instance)
			Instance = new GameProcesser;
		return Instance;}
	static void ReleaseInstance() {
		delete Instance;}
private:
	Key* m_Key;
	MovingTet* m_CurTet;
	NotMovingTet* m_NextTet;
	TargetTet* m_Target;
	Board* m_GameBoard;
public:		// Interface
	bool m_IsGameOver = false;
	bool IsAllInitiated = false;
	void InitAll();
	void UpdateAll();
	void InputKey(const WPARAM& wParam);
	void DrawAll();
	void SetTheirPtrs(Object* TheirOwnPtr);
	void CurTetOnDeadEnd();
	const Board* GetBoard() const { return m_GameBoard; }
	const MovingTet* GetCurTet() const { return m_CurTet; }
	const NotMovingTet* GetNextTet() const { return m_NextTet; }
	const TargetTet* GetTarget() const { return m_Target; }
};

