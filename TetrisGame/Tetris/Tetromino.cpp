#include "stdafx.h"
#include "Tetromino.h"
#include "Key.h"
#include "Board.h"

//////////////Tetromino
Tetromino::Tetromino()
{
	m_Origin.resize(7);
	for (auto B : m_Origin)
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
		m_Origin[TET_Z][2] = new Block(-1, -1, Block::RED);
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


//////////////UseTet
UseTet::UseTet(Board * B) : m_GameBoard(B)
{
	m_Body.resize(4);
	srand(static_cast<unsigned int>(time(NULL)));
}

void UseTet::SetBodyByOrigin()
{
	std::vector<Block*> origin = this->GetOrigin(m_Type);
	for (int i = 0; i < 4; ++i)
	{
		POINT p = origin[i]->GetPoint();
		p.x += m_CenPos.x;
		p.y += m_CenPos.y;
		m_Body[i]->SetPoint(p);
	}
}

bool UseTet::CheckValidPos()
{
	const int EMPTY = 0;
	int width = m_GameBoard->BoardWidth;
	int height = m_GameBoard->BoardHeight;

	for (auto body : m_Body)
	{
		POINT p = body->GetPoint();
		if (p.x <= 0 || p.x >= width)	// boundary of gameboard
			return false;
		if (p.y < 0 || p.y >= height)				// boundary of gameboard
			return false;
		if (m_GameBoard->GetBoard(p))
			return false;
	}
	return true;
}

void UseTet::GoStraightDown()
{
	while (CheckValidPos)
		MoveDown();
}

void UseTet::MoveLeft()
{
	m_CenPos.x--;
	if (CheckValidPos())
		return;
	else
		m_CenPos.x++;
}

void UseTet::MoveRight()
{
	m_CenPos.x++;
	if (CheckValidPos())
		return;
	else
		m_CenPos.x--;
}

void UseTet::MoveDown()
{
	m_CenPos.y++;
	if (CheckValidPos())
		return;
	else
		m_CenPos.y--;
}

void UseTet::Rotate()
{
	// rotate each blocks in counter-clockwise
	std::vector<Block*> tmp = m_Body;
	
	for (auto &t : m_Body)		
	{
		POINT p = t->GetPoint();
		std::swap(p.x, p.y);
		p.x = -p.x;
		t->SetPoint(p);
	}

	if (CheckValidPos())
		return;
	else
		m_Body = tmp;
		return;
}

void UseTet::InputKey(const std::vector<bool>* key)
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

void UseTet::Init()
{
	m_CenPos = { 4,0 };
	m_Type = static_cast<Tetromino::TET_TYPE>(rand() % 7);
	SetBodyByOrigin();
}

void UseTet::Update(const std::vector<bool>* key)
{
	MoveDown();
	if (!CheckValidPos())
	{
		m_GameBoard->NotePile(m_Body);
		return;
	}
	InputKey(key);
	
}

//////////////TargetTet
void TargetTet::SetColor(Tetromino::TET_TYPE Type)
{
	switch (Type)
	{
	case Tetromino::TET_I:
		for (auto B : m_Body)
			B->SetColor(Block::BLUE);
		break;
	case Tetromino::TET_J:
		for (auto B : m_Body)
			B->SetColor(Block::GREEN);
		break;
	case Tetromino::TET_L:
		for (auto B : m_Body)
			B->SetColor(Block::LEMON);
		break;
	case Tetromino::TET_O:
		for (auto B : m_Body)
			B->SetColor(Block::MINT);
		break;
	case Tetromino::TET_S:
		for (auto B : m_Body)
			B->SetColor(Block::ORANGE);
		break;
	case Tetromino::TET_T:
		for (auto B : m_Body)
			B->SetColor(Block::PINK);
		break;
	case Tetromino::TET_Z:
		for (auto B : m_Body)
			B->SetColor(Block::RED);
		break;
	case Tetromino::GRAY:
		for (auto B : m_Body)
			B->SetColor(Block::GRAY);
		break;
	}
}

void TargetTet::SetBodyByOrigin()
{
	std::vector<Block*> origin = this->GetOrigin(m_Type);
	for (int i = 0; i < 4; ++i)
	{
		POINT p = origin[i]->GetPoint();
		p.x += m_CenPos.x;
		p.y += m_CenPos.y;
		m_Body[i]->SetPoint(p);
	}
}

TargetTet::TargetTet(Board * B) : m_GameBoard(B)
{
	m_CenPos = { 4,14 };
	m_Body.resize(4);
}

void TargetTet::Init(UseTet * cur)
{
	m_Type = cur->GetType();
	SetTargetPoint();
	SetBodyByOrigin();
	SetColor(Tetromino::GRAY);
}

