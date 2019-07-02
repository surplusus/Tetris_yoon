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
	srand(time(NULL));		// ���� �߻��� �ʱ�ȭ
	int input;

	//PlaySong(TEXT("����.mp3"));

	cout << ">>>>>>>> Testris <<<<<<<<" << endl;
	cout << ">> 1�ο�, 2�ο� ���� : ";
	cin >> input;

	system("cls");

	if (input == 1)         // 1�ο� 
    {			
		Tetris tetris(Point(0, 0));
		tetris.Run();
	}
	else                    // 2�ο�
    {		
		Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's', 'z');
		Tetris tetris2(Point(38, 0), 'p');

		while (tetris1.IsRunning() || tetris2.IsRunning()) 
        {
			bool key1 = false;
			bool key2 = false;

			if (kbhit())    // Ű �Է��� �ִٸ� 
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