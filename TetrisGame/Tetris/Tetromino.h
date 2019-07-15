#pragma once
#include "Object.h"
#include <vector>
#include <ctime>
class Board;
class Key;
class Block;
class TargetTet;
class NotMovingTet;

class Tetromino : public Object
{
public:
	enum TET_TYPE {	TET_I = 0, TET_J, TET_L,
		TET_O, TET_S, TET_T, TET_Z, GRAY	};
public:
	Tetromino();
	virtual ~Tetromino();
private:
	std::vector<std::vector<Block*>> m_Origin;
	TET_TYPE m_type;	// use for internal variable
	void SetOrigin();
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
public:
	std::vector<Block*> GetOrigin(Tetromino::TET_TYPE type);
	std::vector<Block*> GetGrayBlock(TET_TYPE type);
};

class MovingTet : public Tetromino
{
public:
	MovingTet(Board* B);
	virtual ~MovingTet();
private:
	Tetromino* m_origin;
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
	Key* m_key;
	TargetTet* m_Target;
	NotMovingTet* m_NextTet;
public:
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
public:		//setters
	void SetBoard(Board* o) { m_GameBoard = o; }
	void SetKey(Key* o) { m_key = o; }
	void SetTarget(TargetTet* o) { m_Target = o; }
	void SetNext(NotMovingTet* o) { m_NextTet = o; }
private:	// Move Functions
	void (MovingTet::*MoveFunc)(void);
	void MoveLeft();
	void MoveRight();
	void Rotate();
	void MoveDown();
private:
	void SetBodyByOrigin();
	bool CheckValidPos();
	bool CheckValidPos(POINT & pos);
	bool CheckValidPos(void(MovingTet::*Func)(void));
	void GoStraightDown();
public:
	bool IsDeadEnd();
	Tetromino* GetOrigin() { return m_origin; }
	void Restart();
	void SetCenPos(int x, int y) { m_CenPos.x = x; m_CenPos.y = y; }
	void ApplyKey(const Key* key);
	const TET_TYPE GetType() const { return m_Type; }
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

class NotMovingTet : public Tetromino {
private:
	Tetromino* m_origin;
	POINT m_CenPos;
	TET_TYPE m_Type;
	MovingTet* m_CurTet;
public:
	NotMovingTet();
	virtual ~NotMovingTet();
public:
	std::vector<Block*> m_Body;
	TET_TYPE GetType() { return m_Type; }
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
public:	//setter
	void SetCurrent(MovingTet* o) { m_CurTet = o; }
private:
	void SetBodyByOrigin();
	void Renewal();
};

class TargetTet : public Tetromino
{
private:
	//Tetromino* m_origin;
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
	MovingTet* m_Model;
public:
	TargetTet(Board* B);
	virtual ~TargetTet();
public:
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
public:		//setters
	void SetModel(MovingTet* cur) { m_Model = cur; }
	void SetBoard(Board* GB) { m_GameBoard = GB; }
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
private:
	void SetValidBodyByBoard();
	void SetBodyByModel();
	bool CheckValidPos(std::vector<POINT> &points);
	void Remodel();
public:
	const POINT GetCenPos() const { return m_CenPos; }
};

