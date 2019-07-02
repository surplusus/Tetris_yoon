#include "Tetromino.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>

#define COL				GetStdHandle(STD_OUTPUT_HANDLE)
#define DARK_BLUE		SetConsoleTextAttribute(COL, 0x0001);
#define GREEN			SetConsoleTextAttribute(COL, 0x0002);
#define PURPLE			SetConsoleTextAttribute(COL, 0x0005);
#define ORIGINAL		SetConsoleTextAttribute(COL, 0x0007);
#define SKY_BLUE		SetConsoleTextAttribute(COL, 0x000b);
#define RED				SetConsoleTextAttribute(COL, 0x000c);
#define PLUM			SetConsoleTextAttribute(COL, 0x000d);
#define YELLOW			SetConsoleTextAttribute(COL, 0x000e);

using namespace std;

int Draw_count = 0;

Point g_tetromino_pattern[7][4][4] = // 미노갯수/ 회전 / 4개?
{
    { { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) } },  // I
    { { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, 1) },
      { Point(0, 1), Point(0, 0), Point(1, 1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1) } },  // J
    { { Point(-1, 1), Point(0, 1), Point(0, 0), Point(0, -1) }, { Point(1, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, -1) } }, // L
    { { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },
      { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) } },  // O
    { { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) },
      { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) } },  // S
    { { Point(0, 1), Point(-1, 0), Point(0, 0), Point(0, -1) }, { Point(0, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) } },  // T
    { { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) },
      { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) } }  // Z
};

Tetromino::Tetromino(Board *board, TETROMINO_TYPE type) : board_(board), type_(type)
{
    rotate_ = 0;
}

void Tetromino::Draw(Point reference_pos)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		reference_pos.SetX(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX());
		reference_pos.SetY(center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());
		reference_pos = Point::GetScrPosFromCurPos(reference_pos);
		Point::GotoXY(reference_pos.GetX(), reference_pos.GetY());
		if (type_ == 0) { GREEN cout << "■"; }
		else if (type_ == 1) { DARK_BLUE cout << "■"; }
		else if (type_ == 2) { SKY_BLUE cout << "■"; }
		else if (type_ == 3) { RED cout << "■"; }
		else if (type_ == 4) { YELLOW cout << "■"; }
		else if (type_ == 5) { PURPLE cout << "■"; }
		else { PLUM cout << "■"; }
		Draw_count++;
		if (Draw_count < 700)
		{
			Point::GotoXY(reference_pos.GetX(), 21);
			cout << "▲";
		}
	}
}

void Tetromino::Erase(Point reference_pos)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		reference_pos.SetX(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX());
		reference_pos.SetY(center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());
		reference_pos = Point::GetScrPosFromCurPos(reference_pos);
		Point::GotoXY(reference_pos.GetX(), reference_pos.GetY());
		cout << "  ";
		Point::GotoXY(reference_pos.GetX(), 21);
		ORIGINAL cout << "▦";
	}
}

void Tetromino::SetCenterPos(Point pos)
{
    center_pos_ = pos;
}

void Tetromino::SetScrCenterPos()
{
	scrcenter_pos = Point::GetScrPosFromCurPos(center_pos_);
}

bool Tetromino::MoveDown(Point reference_pos)
{
	center_pos_.SetY(center_pos_.GetY() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		Erase(reference_pos);
		center_pos_.SetY(center_pos_.GetY() - 1);
		Draw(reference_pos);
	}
	else 
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		return false;
	}
}

void Tetromino::MoveRight(Point reference_pos) // 이거보고 나머지방향 해결!
{
    center_pos_.SetX(center_pos_.GetX() + 1);

    if (CheckValidPos()) // 맵을 벗어나진 않았는가
    {
        center_pos_.SetX(center_pos_.GetX() - 1);
        Erase(reference_pos);
        center_pos_.SetX(center_pos_.GetX() + 1);
        Draw(reference_pos);
    }
    else
    {
        center_pos_.SetX(center_pos_.GetX() - 1);
    }
}

void Tetromino::MoveLeft(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
		Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() - 1);
		Draw(reference_pos);
	}
	else
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
	}
}

void Tetromino::Rotate(Point reference_pos)
{
	if (rotate_ != 3)
		rotate_++;
	else 
		rotate_ = 0;
	if (CheckValidPos())
	{
		if (rotate_ == 0) 
			rotate_ = 3;
		else 
			rotate_--;
		Erase(reference_pos);
		if (rotate_ != 3)
			rotate_++;
		else 
			rotate_ = 0;
		Draw(reference_pos);
	}
	else
	{
		if (rotate_ == 0)
			rotate_ = 3;
		else 
			rotate_--;
	}
}

void Tetromino::GoBottom(Point reference_pos)
{
    while (MoveDown(reference_pos))
    {
        Sleep(0.1);
    }
}

bool Tetromino::CheckValidPos(void)
{
    for (int i = 0; i < 4; i++)
    {
        Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

        if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
            return false;
        if (cur_pos.GetY() < 0)
            return false;
        if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
            return false;
    }
    return true;
}

void Tetromino::MarkCurTetrominoPos(Point reference_pos)
{
	int i;
	for (i = 0; i<4; i++)
	{
		reference_pos.SetX(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX());
		reference_pos.SetY(center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());
		board_->SetState(reference_pos, 1);
	}
}

bool Tetromino::CheckEndCondition(void)
{
	if (board_->GetState(g_cur_tetromino_init_pos) != EMPTY)
		return true;
	else
		return false;
}