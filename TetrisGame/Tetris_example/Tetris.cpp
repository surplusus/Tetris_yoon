#include "Tetris.h"
#include "Controller.h"
#include "Tetromino.h"
#include "Score.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <iomanip>

#define COL				GetStdHandle(STD_OUTPUT_HANDLE)
#define ORIGINAL		SetConsoleTextAttribute(COL, 0x0007);

using namespace std;

Tetris::Tetris(Point reference_pos, int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space) : reference_pos_(reference_pos) 
{ 
    running_ = true; 
    cur_tetromino_ = NULL;
    next_tetromino_ = NULL;
    start_time_ = clock();
    falling_speed_ = 0.8;

    SetCursorInvisible(); // 깜빡거리는 커서 지우는거

    controller_.SetController(key_esc, key_right, key_left, key_rotate, key_down, key_space);
    DrawBoard();
    GenerateNextTetromino();
    GetCurTetrominoFromNext();
    GenerateNextTetromino();
    cur_tetromino_->Draw(reference_pos_);
    next_tetromino_->Draw(reference_pos_);
    score_.Print(reference_pos_);
}

void Tetris::DrawBoard(void)
{
    int i;

	Point::GotoXY(reference_pos_);
	cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
	for (i = 0; i < 20; i++)
	{
		if (i == 11)
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦ → 오른쪽  ▦";
		}
		else if (i == 13)
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦  ← 왼쪽   ▦";
		}
		else if (i == 15)
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦  ↑ 회전   ▦";
		}
		else if (i == 17 )
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦  ↓ 아래   ▦";
		}
		else if (i == 19)
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦ SPACE 낙하 ▦";
		}
		else if (i == 6 || i == 10)
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦▦▦▦▦▦▦▦";
		}
		else
		{
			Point::GotoXY(reference_pos_ + Point(0, i + 1));
			cout << "▦                    ▦            ▦";
		}
	}
	Point::GotoXY(reference_pos_ + Point(0, i + 1));
	cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
}

void Tetris::Run(void)
{
    while (running_) 
    {
        RunStep();
    }
}

void Tetris::RunStep(void)
{
    if (_kbhit()) 
    {
        int key = Controller::GetKey();
        KeyHandler(key);
    }
    else 
    {
        NormalStep();		
    }
}

bool Tetris::KeyHandler(int key)
{
    if (key == controller_.Getkey_esc()) 
    {
        running_ = false;
        return true;
    }
    else if (key == controller_.Getkey_right()) 
    {
        cur_tetromino_->MoveRight(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_left()) 
    {
        cur_tetromino_->MoveLeft(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_rotate()) 
    {
        cur_tetromino_->Rotate(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_down()) 
    {
        cur_tetromino_->MoveDown(reference_pos_);
        return true;
    }
	else if (key == controller_.Getkey_space())
	{
		cur_tetromino_->GoBottom(reference_pos_);
		return true;
	}
    return false;
}

void Tetris::NormalStep(void)
{
	int Stage = score_.Stage();

	if ( Stage == 1)
		falling_speed_ = 0.8;
	else if ( Stage == 2)
		falling_speed_ = 0.6;
	else if ( Stage == 3)
		falling_speed_ = 0.4;
	else if ( Stage == 4)
		falling_speed_ = 0.2;
	else if ( Stage == 5)
		falling_speed_ = 0.1;
	else
		falling_speed_ = 0.05;

    if (GetDiffTime() >= falling_speed_) // 일정시간이 지나면~
    {
        if (cur_tetromino_->MoveDown(reference_pos_)) 
        {
            start_time_ = clock();
        }
        else 
        {	// 끝까지 내려왔음. 후처리
            PrepareNextStep();
        }
    }
}

void Tetris::PrepareNextStep(void)
{
	Point::GotoXY(Point(0, 21)); // 그림자 지워주기위해서
	ORIGINAL cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";

    cur_tetromino_->MarkCurTetrominoPos(reference_pos_); // 다떨어지고 엠프티를 풀로 채워주는거....
    
    int EraseLineCount = board_.CheckLineFull(reference_pos_); // 줄이 꽉찼으면 지우고 위에꺼 그대로 내려주는역할
    if (EraseLineCount > 0) // 4줄이 지워지면 EraseLineCount가 4가 된다!
        score_.UpdateScore(reference_pos_, EraseLineCount); // 한줄이라도 지워졌으면 점수 업데이트.
    if (cur_tetromino_->CheckEndCondition()) // 죽을순간체크하는거 
    {
        running_ = false;
        Point::GotoXY(reference_pos_ + Point(10, 10));
        cout << "The game is over !!!";
        _getch();
    }
    else 
    {
        next_tetromino_->Tetromino::Erase(reference_pos_);		
        GetCurTetrominoFromNext();
        cur_tetromino_->Draw(reference_pos_);
        GenerateNextTetromino();
        next_tetromino_->Draw(reference_pos_);
    }
    start_time_ = clock();
}

void Tetris::GenerateNextTetromino(void)
{
    TETROMINO_TYPE tetromino_type = (TETROMINO_TYPE) (rand() % TETROMINO_TYPE_COUNT);

    next_tetromino_ = new Tetromino(&board_, tetromino_type);
    next_tetromino_->SetCenterPos(g_next_tetromino_init_pos);
}

void Tetris::GetCurTetrominoFromNext(void) 
{
	if (cur_tetromino_ != NULL) 
		delete cur_tetromino_;

	cur_tetromino_ = next_tetromino_;
	cur_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);   
}

double Tetris::GetDiffTime(void)
{
    clock_t CurTime;
    CurTime = clock();	//time(&CurTime);
    return ((double) (CurTime - start_time_) / CLOCKS_PER_SEC);
}

void Tetris::SetCursorInvisible(void)	// 화면 커서를 안 보이게 함
{
    CONSOLE_CURSOR_INFO ci = { 10, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}