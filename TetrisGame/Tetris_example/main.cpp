#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
#include "Tetris.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
void PlaySong(char *fileName)
{
	char  cmd[100], errMsg[100];
	int     errCode;
	wsprintf(cmd, TEXT("open %s type mpegvideo alias MediaFile"), fileName);
	errCode = mciSendString(cmd, NULL, 0, NULL);
	if (errCode == 0)
		mciSendString(TEXT("play MediaFile"), NULL, 0, NULL);
	else {
		mciGetErrorString(errCode, errMsg, sizeof(errMsg));
		MessageBox(0, errMsg, NULL, 0);
	}
}


int main()
{
	srand(time(NULL));		// 난수 발생기 초기화
	int input;

	//PlaySong(TEXT("뱅뱅뱅.mp3"));

	cout << ">>>>>>>> Testris <<<<<<<<" << endl;
	cout << ">> 1인용, 2인용 선택 : ";
	cin >> input;

	system("cls");

	if (input == 1)         // 1인용 
    {			
		Tetris tetris(Point(0, 0));
		tetris.Run();
	}
	else                    // 2인용
    {		
		Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's', 'z');
		Tetris tetris2(Point(38, 0), 'p');

		while (tetris1.IsRunning() || tetris2.IsRunning()) 
        {
			bool key1 = false;
			bool key2 = false;

			if (kbhit())    // 키 입력이 있다면 
            {		
				int key = Controller::GetKey();					
				if (tetris1.IsRunning())
					key1 = tetris1.KeyHandler(key);
				if (tetris2.IsRunning() && !key1)
					key2 = tetris2.KeyHandler(key);				
			}

			if (tetris1.IsRunning() && !key1)
				tetris1.NormalStep();
			if (tetris2.IsRunning() && !key2)
				tetris2.NormalStep();			
		}        
	}

    return 0;
}


/*
int main()
{
	srand(time(NULL));
	Tetris tetris(Point(0, 0));
	tetris.Run();

    return 0;
}
*/