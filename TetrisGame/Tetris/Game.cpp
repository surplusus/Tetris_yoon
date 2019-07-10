#include "stdafx.h"
#include "Game.h"


Game::Game()
{
	m_Key = new Key;
	m_CurTet = new UseTet(m_GameBoard);
	m_NextTet = new UseTet(m_GameBoard);
	m_Target = new TargetTet(m_GameBoard);
	m_GameBoard = new Board(m_CurTet);
}

Game::~Game()
{
	delete m_Key;
	delete m_CurTet;
	delete m_NextTet;
	delete m_Target;
	delete m_GameBoard;
}

void Game::InitAll()
{
	m_CurTet->Init();
	m_NextTet->Init();
	m_Target->Init(m_CurTet);
	m_GameBoard->Init();
}

void Game::InputKey(const WPARAM & wParam)
{
	m_Key->SetKey(wParam);
}
