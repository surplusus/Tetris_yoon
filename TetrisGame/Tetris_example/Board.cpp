#include <iostream>
#include <windows.h>
#include "Board.h"
using namespace std;

#define COL			GetStdHandle(STD_OUTPUT_HANDLE)
#define ORIGINAL	SetConsoleTextAttribute(COL, 0x0007);

Board::Board()
{
	int i, j;

	for (i = 0; i < 10; i++) 
    {
		for (j = 0; j < 20; j++)
			board_[i][j] = EMPTY;
	}
}

int Board::GetState(Point pos)
{ 
	return board_[pos.GetX()][pos.GetY()]; 
}

void Board::SetState(Point pos, int state) 
{ 
	board_[pos.GetX()][pos.GetY()] = state;	
}

int Board::CheckLineFull(Point reference_pos)
{
	int count = 0, check = 0;

	for (int val = 0; val < 19; val++)
	{
		for (int y = 0; y < 20; y++)  // 열
		{
			for (int x = 0; x < 10; x++)  // 행
			{
				if (board_[x][y] == EMPTY)   // 해당 행이 하나라도 비어있다면
				{
					check++;
					break;
				}
			}
			if (check == 0)  //해당 행이 꽉차있다면
			{
				count++;
				for (int j = y + 1; j < 19; j++)
				{
					for (int i = 0; i < 10; i++)
					{
						Point::GotoXY(2 * (i + reference_pos.GetX()) + 2, -j + 21);
						cout << "  ";
						board_[i][j - 1] = EMPTY;
					}
					for (int i = 0; i < 10; i++)
						board_[i][j - 1] = board_[i][j];
				}

				for (int i = 0; i < 10; i++)
					board_[i][19] = EMPTY;

				for (int j = 0; j < 20; j++)
				{
					for (int i = 0; i < 10; i++)
					{
						if (board_[i][j] != EMPTY)
						{
							Point::GotoXY(2 * (i + reference_pos.GetX()) + 2, -j + 20);
							ORIGINAL cout << "■";
						}
						else
						{
							Point::GotoXY(2 * (i + reference_pos.GetX()) + 2, -j + 20);
							cout << "  ";
						}
					}
				}
			}
			check = 0;
		}
	}
	return count;
}