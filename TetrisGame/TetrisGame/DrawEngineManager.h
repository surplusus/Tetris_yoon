#pragma once
#include "DrawEngine.h"

// when Game class is NULL, use
// 
class NullGame : public Game {	
public:
	NullGame() {}
	~NullGame() {}
};

class DrawEngineManager
{
private:
	DrawEngineManager() { nullgame = new NullGame; }
	DrawEngineManager(DrawEngineManager & de) {}
	~DrawEngineManager() { delete nullgame; }
	static DrawEngineManager *Instance;
public:
	static DrawEngineManager* GetInstance() {
		if (!Instance)
			Instance = new DrawEngineManager;
		return Instance;
	}
	static void ReleaseInstance() {
		delete Instance;
	}
private:
	DrawEngine *DE;
	Game *nullgame;		// 
public:
	void Initiate(const HWND & hwnd, const HDC & hdc) { DE = new DrawEngine(hwnd, hdc); }
	void Render(HDC & hdc);
	Game* AccessGame();
};

