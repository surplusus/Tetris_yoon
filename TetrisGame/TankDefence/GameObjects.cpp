#include "GameObjects.h"
#include <cmath>

void TANK::DrawTank(HDC & hdc, HPEN & boldpen, HBRUSH & bluebrush)
{
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, bluebrush);
	HPEN oldpen = (HPEN)SelectObject(hdc, boldpen);
	(HPEN)SelectObject(hdc, oldpen);
	Pie(hdc, center.x-50, center.y-50, center.x + 50, center.y + 50, center.x+50, center.y, center.x-50, center.y);
	(HBRUSH)SelectObject(hdc, oldbrush);
	(HPEN)SelectObject(hdc, boldpen);
	MoveToEx(hdc, center.x, center.y, NULL);
	LineTo(hdc, barrel.x, barrel.y);
	SelectObject(hdc, oldpen);
}

void TANK::RotateBarrel(int key, const int &speed)
{
	if (key == RIGHT)
		theta += speed * (PI / 180);
	if (key == LEFT)
		theta -= speed * (PI / 180);
	
	normBarrel.x = std::cos(theta);
	normBarrel.y = std::sin(theta);
	barrel.x = normBarrel.x * dist + center.x;
	barrel.y = normBarrel.y * dist + center.y;
}

void BULLET::DrawBullet(HDC &hdc, HPEN &boldpen, HBRUSH &goldbrush)
{
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, goldbrush);
	Ellipse(hdc, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);
	(HBRUSH)SelectObject(hdc, oldbrush);
}

bool BULLET::CheckLife()
{
	if (pos.y <= 0 || pos.x <= 0 || pos.x >= 700 || pos.y >= 500)
	{
		life = false;
		return false;
	}
}

void BRICK::DrawBrick(HDC & hdc, HPEN & blackpen, HBRUSH & soilbrush)
{
	int width = 40; int height = 20;
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, soilbrush);
	HPEN oldpen = (HPEN)SelectObject(hdc, blackpen);

	Rectangle(hdc, pos.x - width, pos.y - height, pos.x + width, pos.y + height);

	SelectObject(hdc, oldbrush);
	SelectObject(hdc, oldpen);
}

bool Circlecollider::IsTriger(Vector2 other)
{
	float dist = Vector2::DistTwoDot(other, pos);
	if (dist <= r)
	{
		triger = true;
		return true;
	}
	else
	{
		triger = true;
		return false;
	}
}

void ENEMY::CheckLife(Vector2 other)
{
	if (collider.IsTriger(other))
	{
		life = false;
	}
}
