#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	// initialize gameboard
	_gameboard.resize(boardHeight);
	for (int i = 0; i < boardHeight; ++i)
	{
		_gameboard[i].resize(boardWidth);
		for (auto &b : _gameboard[i])
			b = EMPTY;
	}
	// initialize nextblockboard
	_nextBlockBoard.resize(3);
	for (int i = 0; i < 3; ++i)
	{
		_nextBlockBoard[i].resize(3);
		for (auto &b : _nextBlockBoard[i])
			b = EMPTY;
	}
}

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
		// Erase Pileblock
		auto b = _piledBlock.begin();
		for (; b != _piledBlock.end();)
		{
			if ((*b).y == idx)
				_piledBlock.erase(b);
			else
				b++;
		}
}
