#pragma once
#include <Windows.h>
#include "vector2.h"

const float PI = atan2(1, 1) * 4;
const int SPEED = 10;

enum {
	LEFT = 1, RIGHT = 2, SPACE = 3,
};

struct Circlecollider
{
	Vector2 pos;
	int r;
	bool triger = 0;
	bool IsTriger(Vector2 other);
};

class BRICK {
private:
	Vector2 pos;
	bool life;
public:
	BRICK(int x, int y) : pos(x,y) {}
	//bool CheckLife();
	void DrawBrick(HDC & hdc, HPEN &hpen, HBRUSH &hbrush);
};

class BULLET {
public:
	Vector2 pos;
	Vector2 dir;
	bool life;
	BULLET(const Vector2 & vcen, const Vector2 & vbar) : pos(vbar) {
		dir = vbar.Normalize(vcen.x, vcen.y) * 10;
	}
	void DrawBullet(HDC &hdc, HPEN &hpen, HBRUSH &hbrush);
	bool CheckLife();
};

class TANK {
public:
	const float dist = 50;
	Vector2 center;
	Vector2 barrel;
	Vector2 normBarrel;
	float theta = 3 * PI / 2;
public:
	TANK() : center(350,450), barrel(350,400), normBarrel(0,1) {}
	void DrawTank(HDC &hdc, HPEN &hpen, HBRUSH &hbrush);
	void RotateBarrel(int key, const int &speed);
};

class ENEMY {
private:
	Vector2 pos;
	Vector2 dir;
	bool life = 1;
	Circlecollider collider;
public:
	ENEMY(int x, int y) : pos(x, y), dir(0, SPEED) {
		collider.pos = pos; collider.r = 50;
	}
	void CheckLife(Vector2 collier);
};