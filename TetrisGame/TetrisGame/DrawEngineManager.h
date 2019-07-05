#pragma once
#include "DrawEngine.h"

class DrawEngineManager
{
private:
	DrawEngineManager() {}
	DrawEngineManager(DrawEngineManager & de) {}
	~DrawEngineManager() {}
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
public:
	void Initiate(const HWND & hwnd, const HDC & hdc) { DE = new DrawEngine(hwnd, hdc); }
	void Render() { DE->Render(); }
};

