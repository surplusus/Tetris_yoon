#include "stdafx.h"
#include "Game.h"
#include "Tetromino.h"

GameProcesser* GameProcesser::Instance = nullptr;

GameProcesser::GameProcesser()
{
	m_Key = new Key;
	m_CurTet = new MovingTet(m_GameBoard);
	m_NextTet = new NotMovingTet();
	m_Target = new TargetTet(m_GameBoard);
	m_GameBoard = new Board(m_Target);
}

GameProcesser::~GameProcesser()
{
	delete m_Key;
	delete m_CurTet;
	delete m_NextTet;
	delete m_Target;
	delete m_GameBoard;
}

void GameProcesser::InitAll()
{
	m_CurTet->Init();
	m_NextTet->Init();
	m_Target->Init();
	m_GameBoard->Init();
	if (m_CurTet != nullptr || m_NextTet != nullptr ||
		m_Target != nullptr || m_GameBoard != nullptr)
		IsAllInitiated = true;
}

void GameProcesser::UpdateAll()
{
	m_Target->Update();	//타겟을 만들고
	m_CurTet->ApplyKey(m_Key);
	m_Key->ClearKey();
	m_CurTet->Update();	//타겟에 맞춰지면 바뀜
	m_NextTet->Update();//바껴지면 다른 블럭 나타내기(콜백쓰기)
	
}

void GameProcesser::InputKey(const WPARAM & wParam)
{
	m_Key->SetKey(wParam);
}

void GameProcesser::DrawAll()
{
	Renderer* R = Renderer::GetInstance();
	R->SetFuncPtr("back");
	m_GameBoard->Draw();
	R->SetFuncPtr("main");
	m_CurTet->Draw();
	m_Target->Draw();
	R->SetFuncPtr("mini");
	m_NextTet->Draw();
	
}

void GameProcesser::SetTheirPtrs(Object* TOP)
{
	if (TOP == m_CurTet)
	{
		m_CurTet->SetBoard(static_cast<Board*>(m_GameBoard));
		m_CurTet->SetKey(static_cast<Key*>(m_Key));
		m_CurTet->SetTarget(static_cast<TargetTet*>(m_Target));
		m_CurTet->SetNext(static_cast<NotMovingTet*>(m_NextTet));
	}
	else if (TOP == m_NextTet)
	{
		m_NextTet->SetCurrent(static_cast<MovingTet*>(m_CurTet));
	}
	else if (TOP == m_Target)
	{
		m_Target->SetBoard(static_cast<Board*>(m_GameBoard));
		m_Target->SetModel(static_cast<MovingTet*>(m_CurTet));
	}
	else if (TOP == m_GameBoard)
	{
		m_GameBoard->SetTarget(static_cast<TargetTet*>(m_Target));
	}
	else
		std::cout << "Who the hack are you!" << std::endl;
}

void GameProcesser::CurTetOnDeadEnd()
{
	m_GameBoard->SetTarget(m_Target);
	m_GameBoard->Update();
	m_NextTet->Update();
}
