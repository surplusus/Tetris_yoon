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
	int Rand();	// ���� �����
	int DeltaTime();  // ���ؽð��� ���� ����ð� ǥ��
	void SetBasePeriod();	// ���ؽð� ���ϱ�
	void DrawTime();  // ����ð� ǥ��
};

