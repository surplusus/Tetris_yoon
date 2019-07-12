#include "stdafx.h"
#include "Tetromino.h"
#include "Key.h"
#include "Board.h"
#include "Block.h"

//////////////Tetromino
Tetromino::Tetromino()
{
	m_Origin.resize(7);
	for (auto &B : m_Origin)
		B.resize(4);
	SetOrigin();
}

Tetromino::~Tetromino()
{
	for (auto B : m_Origin)
		for (auto C : B)
			delete C;
}

void Tetromino::SetOrigin()
{
	// Tetromino::TET_I:
		m_Origin[TET_I][0] = new Block(-1, 0, Block::BLUE);
		m_Origin[TET_I][1] = new Block(0, 0, Block::BLUE);
		m_Origin[TET_I][2] = new Block(1, 0, Block::BLUE);
		m_Origin[TET_I][3] = new Block(2, 0, Block::BLUE);
	// Tetromino::TET_J:
		m_Origin[TET_J][0] = new Block(0, 1, Block::GREEN);
		m_Origin[TET_J][1] = new Block(0, 0, Block::GREEN);
		m_Origin[TET_J][2] = new Block(1, 0, Block::GREEN);
		m_Origin[TET_J][3] = new Block(2, 0, Block::GREEN);
	// Tetromino::TET_L:
		m_Origin[TET_L][0] = new Block(0, -1, Block::LEMON);
		m_Origin[TET_L][1] = new Block(0, 0, Block::LEMON);
		m_Origin[TET_L][2] = new Block(1, 0, Block::LEMON);
		m_Origin[TET_L][3] = new Block(2, 0, Block::LEMON);
	// Tetromino::TET_O:
		m_Origin[TET_O][0] = new Block(1, 0, Block::MINT);
		m_Origin[TET_O][1] = new Block(0, 0, Block::MINT);
		m_Origin[TET_O][2] = new Block(0, 1, Block::MINT);
		m_Origin[TET_O][3] = new Block(1, 1, Block::MINT);
	// Tetromino::TET_S:
		m_Origin[TET_S][0] = new Block(-1, 0, Block::ORANGE);
		m_Origin[TET_S][1] = new Block(0, 0, Block::ORANGE);
		m_Origin[TET_S][2] = new Block(0, 1, Block::ORANGE);
		m_Origin[TET_S][3] = new Block(1, 1, Block::ORANGE);
	// Tetromino::TET_T:
		m_Origin[TET_T][0] = new Block(1, 0, Block::PINK);
		m_Origin[TET_T][1] = new Block(0, 0, Block::PINK);
		m_Origin[TET_T][2] = new Block(-1, 0, Block::PINK);
		m_Origin[TET_T][3] = new Block(0, 1, Block::PINK);
	// Tetromino::TET_Z:
		m_Origin[TET_Z][0] = new Block(0, 1, Block::RED);
		m_Origin[TET_Z][1] = new Block(0, 0, Block::RED);
		m_Origin[TET_Z][2] = new Block(0, -1, Block::RED);
		m_Origin[TET_Z][3] = new Block(1, 0, Block::RED);
}

std::vector<Block*> Tetromino::GetOrigin(Tetromino::TET_TYPE type)
{
	switch (type)
	{
	case TET_I:
		return m_Origin[TET_I];
	case TET_J:
		return m_Origin[TET_J];
	case TET_L:
		return m_Origin[TET_L];
	case TET_O:
		return m_Origin[TET_O];
	case TET_S:
		return m_Origin[TET_S];
	case TET_T:
		return m_Origin[TET_T];
	case TET_Z:
		return m_Origin[TET_Z];
	default:
		break;
	}
}

//////////////Use & Target 공통부분//////////
UseTet::UseTet(Board * B) : m_GameBoard(B)
{
	m_origin = new Tetromino;
	m_Body.resize(4);
	srand(static_cast<unsigned int>(time(NULL)));
}

UseTet::~UseTet()
{
	for (auto &B : m_Body)
		delete B;
}

TargetTet::TargetTet(Board * B) : m_GameBoard(B)
{
	m_CenPos = { 4,13 };
	m_Body.resize(4);
}

TargetTet::~TargetTet()
{
	for (auto &B : m_Body)
		delete B;
}

void UseTet::Init()
{
	m_CenPos = { 4,1 };
	m_Type = static_cast<Tetromino::TET_TYPE>(rand() % 7);
	m_Target = nullptr;
	for (int i = 0; i < 4; ++i)
		m_Body[i] = new Block(*(m_origin->GetOrigin(m_Type)[i]));
	SetBodyByOrigin();
}

void TargetTet::Init()
{
	m_CenPos = m_Model->m_Body[1]->GetPoint();
	m_CenPos.y = 13;
	m_Type = m_Model->GetType();
	for (int i = 0; i < 4; ++i)
		m_Body[i] = new Block(*(m_Model->GetOrigin()[i]));
	//SetBodyByOrigin();
	SetColor();	// GRAY
}

void UseTet::Update()
{
	if (m_GameBoard->GetBoardType(m_CenPos) == Board::FULL)
	{
		std::cout << "gameover" << std::endl;
		return;
	}
	if (IsActive)
	{
		MoveDown();
		int DeadFlag = 0;
		for (int i = 0; i < 4; ++i)
		{
			POINT me = m_Body[i]->GetPoint();
			POINT you = m_Target->m_Body[i]->GetPoint();
			if (me.x == you.x && me.y == you.y)
				DeadFlag++;
		}
		if (DeadFlag == 4)
		{
			m_GameBoard->Update();
			Restart();
		}
	}
	SetBodyByOrigin();

}

void TargetTet::Update()
{
	Remodel();
	//SetBodyPosByBoard();
	m_CenPos = m_Body[1]->GetPoint();
}

void UseTet::Draw()
{
	Renderer* R = Renderer::GetInstance();

	for (auto B : m_Body)
	{
		R->DrawBlock(*B);
	}
}

void TargetTet::Draw()
{
	Renderer* R = Renderer::GetInstance();

	for (auto B : m_Body)
	{
		R->DrawBlock(*B);
	}
}

/////////

void UseTet::SetBodyByOrigin()
{
	std::vector<Block*> origin = m_origin->GetOrigin(m_Type);
	for (int i = 0; i < 4; ++i)
	{
		POINT p = origin[i]->GetPoint();
		p.x += m_CenPos.x;
		p.y += m_CenPos.y;
		m_Body[i]->SetPoint(p);
	}
}

void TargetTet::SetBodyByModel()
{
	for (int i = 0; i < 4; ++i)
	{
		POINT p = m_Model->m_Body[i]->GetPoint();
		m_Body[i]->SetPoint(p);
	}
	m_CenPos = m_Model->m_Body[1]->GetPoint();
}

bool UseTet::CheckValidPos()
{
	const int EMPTY = 0;
	int width = m_GameBoard->BoardWidth;
	int height = m_GameBoard->BoardHeight;

	for (auto &body : m_Body)
	{
		POINT p = body->GetPoint();
		if (p.x <= 0 || p.x >= width)	// boundary of gameboard
			return false;
		if (p.y < 0 || p.y >= height)				// boundary of gameboard
			return false;
		if (m_GameBoard->GetBoardType(p))
			return false;
	}
	return true;
}

bool UseTet::CheckValidPos(POINT & p)
{
	int width = m_GameBoard->BoardWidth;
	int height = m_GameBoard->BoardHeight;
	if (p.x <= 0 || p.x >= width)	// boundary of gameboard
		return false;
	if (p.y < 0 || p.y >= height)				// boundary of gameboard
		return false;
	if (m_GameBoard->GetBoardType(p))
		return false;
	
	return true;
}

bool TargetTet::CheckValidPos()
{
	int width = m_GameBoard->BoardWidth-1;
	int height = m_GameBoard->BoardHeight-1;

	for (auto body : m_Body)
	{
		POINT p = body->GetPoint();
		p.y++;
		if (p.x < 0 || p.x > width)	// boundary of gameboard
			return false;
		if (p.y < 0 || p.y > height)	// boundary of gameboard
			return false;
		if (m_GameBoard->GetBoardType(p))
			return false;
	}
	return true;
}

//////////////UseTet/////////

void UseTet::GoStraightDown()
{
	while (!CheckValidPos())
		MoveDown();
}

void UseTet::MoveLeft()
{
	if((m_CenPos.x - 1) >= 0)
		m_CenPos.x--;
}

void UseTet::MoveRight()
{
	//m_CenPos.x++;
	///*if (CheckValidPos())
	//	return;
	//else
	//	m_CenPos.x--;*/
	//while (!CheckValidPos())
	//	m_CenPos.x--;
	if ((m_CenPos.y + 1) < Board::BoardWidth)
		m_CenPos.x++;
}

void UseTet::MoveDown()
{
	if ((m_CenPos.y + 1) <= Board::BoardHeight && CheckValidPos())
		m_CenPos.y++;
}

void UseTet::Rotate()
{
	// rotate each blocks in counter-clockwise
	std::vector<POINT> tmp;
	for (int i = 0; i < 4; ++i)
		tmp.push_back(m_Body[i]->GetPoint());
	int DeadFlag = 0;
	POINT center = tmp[1];

	for (auto &p : tmp)
	{
		POINT t = p;
		p.x = center.x - (center.y - t.y);
		p.y = center.y + (center.x - t.x);
		if (!CheckValidPos(p))
			DeadFlag++;
	}

	if (!DeadFlag)
	{
		for (int i = 0; i < 4; ++i)
			m_Body[i]->SetPoint(tmp[i]);
	}
}

void UseTet::TurnOnActive(TargetTet* target)
{
	IsActive = true;
	m_Target = target;
}

void UseTet::Restart()
{
	m_CenPos = { 4,1 };
	m_Type = static_cast<Tetromino::TET_TYPE>(rand() % 7);
	SetBodyByOrigin();
}

void UseTet::ApplyKey(const Key* key)
{
	auto k = *key;
	if (k[Key::SPACE] == true)
		GoStraightDown();
	if (k[Key::LEFT] == true)
		MoveLeft();
	if (k[Key::RIGHT] == true)
		MoveRight();
	if (k[Key::DOWN] == true)
		MoveDown();
	if (k[Key::UP] == true)
		Rotate();
}



//////////////TargetTet/////////
void TargetTet::Remodel()
{
	m_Type = m_Model->GetType();
	SetColor();
	SetBodyByModel();
	
	while(CheckValidPos())
	{
		for (auto B : m_Body)
		{
			POINT p = B->GetPoint();
			p.y++;
			B->SetPoint(p);
		}
	}
}

void TargetTet::SetColor()
{
	for (auto &B : m_Body)
		B->SetColor(Block::COLOR_TYPE::ORANGE);
}

void TargetTet::SetBodyPosByBoard()
{

	while (!CheckValidPos())
	{
		for (auto &t : m_Body)
		{
			POINT p = t->GetPoint();
			p.y--;
			t->SetPoint(p);
		}
	}
		
}
