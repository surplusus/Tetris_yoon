#include "Managers.h"
#include <cmath>
#include <ctime>


InGameManager::InGameManager()
{
	int gap = 70;
	for (int i = 0; i < 10; ++i)
	{
		BRICK* b = new BRICK(35+i*gap,400);
		brick.push_back(b);
	}
	tank = new TANK();
}

InGameManager::~InGameManager()
{

	delete tank;
	for (auto & i : brick)
		delete i;
	for (auto & i : bullet)
		delete i;
	for (auto & i : enemy)
		delete i;
}

void InGameManager::Render(HDC & hdc)
{
	HPEN boldPen = CreatePen(PS_SOLID, 10, RED);
	HPEN blackPen = CreatePen(PS_SOLID, 1, BLACK);
	HBRUSH blueBrush = CreateSolidBrush(BLUE);
	HBRUSH goldBrush = CreateSolidBrush(GOLD);
	HBRUSH soilBrush = CreateSolidBrush(SOIL);

	for (BRICK* K : brick)
		K->DrawBrick(hdc, blackPen, soilBrush);

	tank->DrawTank(hdc, boldPen, blueBrush);
	
	for (BULLET* B : bullet)
		B->DrawBullet(hdc,boldPen,goldBrush);

	DeleteObject(boldPen);
	DeleteObject(blackPen);
	DeleteObject(soilBrush);
	DeleteObject(blueBrush);
	DeleteObject(goldBrush);
}

void InGameManager::Update()
{
	double nowtime = clock();
	int key = GetKey();
	// 포신 돌리기
	tank->RotateBarrel(key,SPEED);

	/////// 총알 관련 //////
	// 총알 생성
	if (key == 3 && (nowtime - prevtime >= 500))
	{
		BULLET *newb = new BULLET(tank->center, tank->barrel);
		bullet.push_back(newb);
		prevtime = nowtime;
	}
	std::list<BULLET*>::iterator it;
	for (it = bullet.begin(); it != bullet.end();)
	{
		BULLET *B = *it;
		// 총알 위치 변경
		B->pos += B->dir;
		// 총알 생명
		if (!B->CheckLife())
		{
			it = bullet.erase(it);
			delete B;
		}
		else
			++it;
	}

	/////// 적 관련 //////
	// 첫 적 생성
	double timegap = 1000;
	if (enemyspawntime == 0.0)
	{
		enemyspawntime = clock();
		ENEMY* tmp = new ENEMY;

	}
	if (nowtime - enemyspawntime >= timegap)
	{

	}
}
