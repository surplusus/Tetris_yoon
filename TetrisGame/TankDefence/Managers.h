#pragma once
#include <Windows.h>
#include <vector>
#include <list>

class ManagerInterface
{
protected:
	#define BLACK RGB(0,0,0)
	#define WHITE RGB(255,255,255)
	#define BLUE RGB(66, 135, 245)
	#define GOLD RGB(227, 224, 48)
	#define RED RGB(217, 56, 129)
	#define SOIL RGB(245, 105, 66)
public:

	virtual void Update() = 0;
	virtual void Render(HDC & hdc) = 0;
private:
	int inputKey = 0;
public:
	virtual void SetKey(int Key) = 0;
	virtual int GetKey() = 0;
};

#include "GameObjects.h"

class BRICK;
class BULLET;
class ENEMY;
class TANK;

class InGameManager : public ManagerInterface
{

public:
	InGameManager();
	~InGameManager();
private:
	const int SPEED = 10;
	double prevtime = 0.0;
	double enemyspawntime = 0.0;
	int inputKey = 0;
	std::vector<BRICK*> brick;
	std::list<BULLET*> bullet;
	TANK* tank;
	std::list<ENEMY*> enemy;
public:
	void Render(HDC & hdc);
	void Update();
	void SetKey(int Key) { inputKey = Key; }
	int GetKey() { int tmp = inputKey; inputKey = 0; return tmp; }
};

class LoginManager : public ManagerInterface
{
private:	
	int inputKey = 0;
public:
	void Update() {}
	void Render(HDC & hdc) {}
	void SetKey(int Key) { inputKey = Key; }
	int GetKey() { int tmp = inputKey; inputKey = 0; return tmp; }
};

class RankManager : public ManagerInterface
{
private:
	int inputKey = 0;
public:
	void Update() {}
	void Render(HDC & hdc) {}
	void SetKey(int Key) { inputKey = Key; }
	int GetKey() { int tmp = inputKey; inputKey = 0; return tmp; }
};
