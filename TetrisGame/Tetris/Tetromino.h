#pragma once
#include "Object.h"
#include <vector>
#include <ctime>
class Board;
class Key;
class Block;
class TargetTet;

class Tetromino : public Object
{
public:
	Tetromino();
	virtual ~Tetromino();
private:
	std::vector<std::vector<Block*>> m_Origin;
public:
	enum TET_TYPE {	TET_I = 0, TET_J, TET_L, 
				TET_O, TET_S, TET_T, TET_Z, GRAY};
public:
	std::vector<Block*> GetOrigin(Tetromino::TET_TYPE type);
	void SetOrigin();
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
};

class UseTet : public Tetromino
{
public:
	UseTet(Board* B);
	virtual ~UseTet();
private:
	Tetromino* m_origin;
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
	Key* m_key;
	TargetTet* m_Target;
	
public:
	bool IsActive = false;
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
private:
	void SetBodyByOrigin();
	bool CheckValidPos();
	bool CheckValidPos(POINT & pos);
	void GoStraightDown();
	void MoveLeft();
	void MoveRight();
	void Rotate();
	void Restart();
public:
	std::vector<Block*> GetOrigin() { return m_origin->GetOrigin(m_Type); }
	void TurnOnActive(TargetTet* target);
	void MoveDown();
	void SetCenPos(int x, int y) { m_CenPos.x = x; m_CenPos.y = y; }
	void SetBoardKey(Board* GB, Key* key) {
		m_GameBoard = GB, m_key = key;	}
	void ApplyKey(const Key* key);
	const TET_TYPE GetType() const { return m_Type; }
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};


class TargetTet : public Tetromino
{
private:
	//Tetromino* m_origin;
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
	UseTet* m_Model;
public:
	TargetTet(Board* B);
	virtual ~TargetTet();
public:
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
private:
	void SetColor();
	void SetBodyPosByBoard();
	void SetBodyByModel();
	bool CheckValidPos();
	void Remodel();
public:
	void SetModel(UseTet* cur) { m_Model = cur; }
	void SetBoard(Board* GB) { m_GameBoard = GB; }
	const POINT GetCenPos() const { return m_CenPos; }
};

