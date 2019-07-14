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
	// Tetromino::GRAY:
		m_Origin[GRAY][0] = new Block(0, 0, Block::GRAY);
		m_Origin[GRAY][1] = new Block(0, 0, Block::GRAY);
		m_Origin[GRAY][2] = new Block(0, 0, Block::GRAY);
		m_Origin[GRAY][3] = new Block(0, 0, Block::GRAY);
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
	case GRAY:
		return GetGrayBlock(m_type);
	default:
		break;
	}
}

std::vector<Block*> Tetromino::GetGrayBlock(TET_TYPE type)
{
	m_type = type;
	for (int i = 0; i < 4; ++i)
	{
		POINT p = GetOrigin(m_type)[i]->GetPoint();
		m_Origin[GRAY][i]->SetPoint(p);
	}
	return m_Origin[GRAY];
}

//////////////Children 공통부분//////////
MovingTet::MovingTet(Board * B) : m_GameBoard(B)
{
	m_origin = new Tetromino;
	m_GameBoard = nullptr;
	m_key = nullptr;
	m_Target = nullptr;	
	m_NextTet = nullptr;
	m_Body.resize(4);
	srand(static_cast<unsigned int>(time(NULL)));
}

MovingTet::~MovingTet()
{
	delete m_origin;
	for (auto &B : m_Body)
		delete B;
}

NotMovingTet::NotMovingTet()
{
	m_origin = new Tetromino;
	m_Body.resize(4);
	srand(static_cast<unsigned int>(time(NULL)));
}

NotMovingTet::~NotMovingTet()
{
	delete m_origin;
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
	m_GameBoard = nullptr;
	m_Model = nullptr;
	for (auto &B : m_Body)
		delete B;
}

void MovingTet::Init()
{
	m_CenPos = { 4,1 };
	m_Type = static_cast<Tetromino::TET_TYPE>(rand() % 7);
	GameProcesser* GP = GameProcesser::GetInstance();
	GP->SetTheirPtrs(this);
	m_Target = nullptr;
	for (int i = 0; i < 4; ++i)
		m_Body[i] = new Block(*(m_origin->GetOrigin(m_Type)[i]));
	SetBodyByOrigin();
}

void NotMovingTet::Init()
{
	m_CenPos = { 1,1 };
	m_Type = static_cast<Tetromino::TET_TYPE>(rand() % 7);
	GameProcesser* GP = GameProcesser::GetInstance();
	GP->SetTheirPtrs(this);
	for (int i = 0; i < 4; ++i)
		m_Body[i] = new Block(*(m_origin->GetOrigin(m_Type)[i]));
	SetBodyByOrigin();

}

void TargetTet::Init()
{
	GameProcesser* GP = GameProcesser::GetInstance();
	GP->SetTheirPtrs(this);
	m_Type = m_Model->GetType();
	for (int i = 0; i < 4; ++i)
		m_Body[i] = new Block(*(m_Model->m_Body[i]));
	SetBodyByModel();
}

void MovingTet::Update()
{
	GameProcesser* GP = GameProcesser::GetInstance();
	if (m_GameBoard->GetBoardType(m_CenPos) == Board::FULL)
	{
		std::cout << "gameover" << std::endl;
		GP->m_IsGameOver = true;
		return;
	}
	MoveDown();
	if (IsDeadEnd())
	{
		GP->CurTetOnDeadEnd();
	}
}

void NotMovingTet::Update()
{
	m_CurTet->Restart();
	Renewal();
}

void TargetTet::Update()
{
	Remodel();
	SetValidBodyByBoard();
}

void MovingTet::Draw()
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

void NotMovingTet::Draw()
{

}

//////////////SetBody & CheckValiPos//////////

void MovingTet::SetBodyByOrigin()
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

void NotMovingTet::SetBodyByOrigin()
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
		m_Body[i] = m_Model->GetOrigin()->GetGrayBlock(m_Type)[i];
		POINT p = m_Model->m_Body[i]->GetPoint();
		m_Body[i]->SetPoint(p);
	}
	m_CenPos = m_Body[1]->GetPoint();
}

bool MovingTet::CheckValidPos()
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

bool MovingTet::CheckValidPos(POINT & p)
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

bool MovingTet::CheckValidPos(void(MovingTet::*Func)(void))
{
	//MoveFunc = Func;
	if (Func == &MovingTet::MoveDown)
	{
		for (auto B : m_Body)
		{
			POINT p = B->GetPoint();
			p.y++;
			if (m_GameBoard->GetBoardType(p))
				return false;
		}
	}
	else if (Func == &MovingTet::MoveRight)
	{
		for (auto B : m_Body)
		{
			POINT p = B->GetPoint();
			p.x++;
			if (m_GameBoard->GetBoardType(p))
				return false;
		}
	}
	else if (Func == &MovingTet::MoveLeft)
	{
		for (auto B : m_Body)
		{
			POINT p = B->GetPoint();
			p.x--;
			if (m_GameBoard->GetBoardType(p))
				return false;
		}
	}
	else if (Func == &MovingTet::Rotate)
	{
		for (auto B : m_Body)
		{
			POINT p, t;
			p = t = B->GetPoint();
			p.x = m_Body[1]->GetPoint().x - (m_Body[1]->GetPoint().y - t.y);
			p.y = m_Body[1]->GetPoint().y + (m_Body[1]->GetPoint().x - t.x);
			if (m_GameBoard->GetBoardType(p))
				return false;
		}
	}
	return true;
}

bool TargetTet::CheckValidPos(std::vector<POINT> &points)
{
	for (int i = 0; i < 4; ++i)
	{
		bool isFull = m_GameBoard->GetBoardType(points[i]);
		if (isFull)
			return false;
	}
	return true;
}

//////////////Current Movint Tetromino//////////

void MovingTet::GoStraightDown()
{
	while (CheckValidPos(&MovingTet::MoveDown))
		MoveDown();
}

void MovingTet::MoveLeft()
{
	if (CheckValidPos(&MovingTet::MoveLeft))
	{
		for (auto &B : m_Body)
			B->SetXY(B->GetPoint().x - 1, B->GetPoint().y);
	}
}

void MovingTet::MoveRight()
{
	if (CheckValidPos(&MovingTet::MoveRight))
	{
		for (auto &B : m_Body)
			B->SetXY(B->GetPoint().x + 1, B->GetPoint().y);
	}
}

void MovingTet::MoveDown()
{
	if (CheckValidPos(&MovingTet::MoveDown))
	{
		for (auto &B : m_Body)
			B->SetXY(B->GetPoint().x, B->GetPoint().y + 1);
	}
}

void MovingTet::Rotate()
{
	// rotate each blocks in counter-clockwise
	if (CheckValidPos(&MovingTet::Rotate))
	{
		for (auto &B : m_Body)
		{
			POINT p, t;
			p = t = B->GetPoint();
			p.x = m_Body[1]->GetPoint().x - (m_Body[1]->GetPoint().y - t.y);
			p.y = m_Body[1]->GetPoint().y + (m_Body[1]->GetPoint().x - t.x);
			B->SetPoint(p);
		}
	}
}

void MovingTet::Restart()
{
	m_CenPos = { 4,1 };
	m_Type = m_NextTet->GetType();
	SetBodyByOrigin();
}

bool MovingTet::IsDeadEnd()
{
	for (int i = 0; i < 4; ++i)
	{
		POINT p = m_Body[i]->GetPoint();
		POINT t = m_Target->m_Body[i]->GetPoint();
		if (p.x != t.x || p.y != t.y)
			return false;
	}
	return true;
}

void MovingTet::ApplyKey(const Key* key)
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

//////////////Next NotMovint Tetromino/////////

void NotMovingTet::Renewal()
{
	m_Type = static_cast<Tetromino::TET_TYPE>(rand() % 7);
	m_CenPos = { 1,1 };
	SetBodyByOrigin();
}


//////////////TargetTet/////////


void TargetTet::Remodel()
{
	m_Type = m_Model->GetType();
	SetBodyByModel();
}

void TargetTet::SetValidBodyByBoard()
{
	std::vector<POINT> tmp(4);
	for (int i = 0; i < 4; ++i)
		tmp[i] = m_Body[i]->GetPoint();

	while (true)
	{
		for (auto &B : tmp)
			B.y++;

		if (CheckValidPos(tmp))
		{
			for (int i = 0; i < 4; ++i)
			{
				m_Body[i]->SetPoint(tmp[i]);
			}
		}
		else
			break;
	}
}