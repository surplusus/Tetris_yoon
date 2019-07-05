#include "stdafx.h"
#include "Background.h"

bool Background::CheckFullLine()
{
	bool check = false;
	for (int i = 0; i < 12; ++i)
	{
		int full = 0;
		for (int j = 0; j < 8; ++j)
		{
			if (_gameboard[i][j] == FULL)
				full++;
		}
		if (full == 8) {
			_fullLine[i] = FULL;
			check = true;
			EraseLine(i);
			i--;
		}
	}
	return check;
}

void Background::EraseLine(int idx)
{
	_cntLineDeleted++;
		
		// Move rows down from row[idx]
		for (int i = idx; i < 12 - 1; ++i)
		{
			for (int j = 0; j < 8; ++j)
				_gameboard[i][j] = _gameboard[i+1][j];
		}
}
