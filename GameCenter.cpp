#include "stdafx.h"
#include "GameCenter.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
void PlaySong(char *fileName)
{
	TCHAR  cmd[100], errMsg[100];
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


GameCenter::GameCenter()
{
}


GameCenter::~GameCenter()
{
}
