#include "stdafx.h"
#include "Game.h"
#include "Tetromino.h"

Game* Game::Instance = nullptr;

Game::Game()
{
	m_Key = new Key;
	m_CurTet = new UseTet(m_GameBoard);
	m_NextTet = new UseTet(m_GameBoard);
	m_Target = new TargetTet(m_GameBoard);
	m_GameBoard = new Board(m_Target);
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
	m_CurTet->SetBoardKey(m_GameBoard, m_Key);
	m_CurTet->Init();
	m_NextTet->SetBoardKey(m_GameBoard, m_Key);
	m_NextTet->Init();
	m_Target->SetModel(m_CurTet);
	m_Target->SetBoard(m_GameBoard);
	m_Target->Init();
	m_CurTet->TurnOnActive(m_Target);
	m_GameBoard->Init();

}

void Game::UpdateAll()
{
	m_CurTet->ApplyKey(m_Key);
	m_Key->ClearKey();
	m_Target->Update();
	m_CurTet->Update();
	m_NextTet->SetCenPos(1, 1);
	m_NextTet->Update();
	
}

void Game::InputKey(const WPARAM & wParam)
{
	m_Key->SetKey(wParam);
}

void Game::DrawAll()
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
