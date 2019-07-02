#include <iostream>
#include <iomanip>
using namespace std;
#include "Score.h"
#include <Windows.h>

#define COL			GetStdHandle(STD_OUTPUT_HANDLE)
#define GRAY		SetConsoleTextAttribute(COL, 0x0008);

Score::Score()
{
    score_ = 0;
	total_score_ = 0;
	stage = 1;
	stagepos_ = Point(26, 8);
    score_pos_ = Point(28, 9);
	total_score_pos_ = Point(28, 10);
}

void Score::Print(Point reference_pos)
{
	if (score_ >= 2000)
	{
		score_ = 0;
		stage += 1;
	}
	Point::GotoXY(reference_pos + stagepos_);
	GRAY cout << "Stage " << stage;
    Point::GotoXY(reference_pos + score_pos_);
	GRAY cout << setw(5) << score_;
	Point::GotoXY(reference_pos + total_score_pos_);
	GRAY cout << setw(5) << total_score_;

}

void Score::UpdateScore(Point reference_pos, int increment)
{
	if (increment == 1)
	{
		score_ += 100;
		total_score_ += 100;
	}
	else if (increment == 2)
	{
		score_ += 300;
		total_score_ += 300;
	}
	else if (increment == 3)
	{
		score_ += 500; 
		total_score_ += 500;
	}
	else
	{
		score_ += 1000;
		total_score_ += 1000;
	}
		
    Print(reference_pos);
}

int Score::Stage()
{
	return stage;
}

