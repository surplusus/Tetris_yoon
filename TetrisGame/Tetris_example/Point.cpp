#include <windows.h>
#include <conio.h>
#include <ctime>
#include "Point.h"
using namespace std;

Point Point::operator+(const Point &pt)
{
	return Point(x_ + pt.x_, y_ + pt.y_);
}

void Point::GotoXY(int x, int y)		// Ŀ�� ��ġ �̵�
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Point::GotoXY(Point pos)
{
	GotoXY(pos.GetX(), pos.GetY());
}

Point Point::GetScrPosFromCurPos(const Point &pos) // �迭��ǥ�� ȭ����ǥ�� �����´�.
{
	return Point(2 * pos.x_ + 2, (-1) * pos.y_ + 20);
}