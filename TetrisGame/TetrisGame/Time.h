#pragma once
#include <ctime>

class Time
{
private:
	clock_t now;
	clock_t basePeriod;
public:
	Time();
	~Time();
public:
	int Rand();	// 난수 만들기
	int DeltaTime();  // 기준시간과 비교한 경과시간 표시
	void SetBasePeriod();	// 기준시간 정하기
	void DrawTime();  // 현재시간 표시
};

