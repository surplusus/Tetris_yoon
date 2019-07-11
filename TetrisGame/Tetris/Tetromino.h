#pragma once
#include "Object.h"
#include <vector>
#include <ctime>
class Board;
class Key;
class Block;

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
public:
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
private:
	void SetBodyByOrigin();
	bool CheckValidPos();
	void GoStraightDown();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	
public:
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
	Tetromino* m_origin;
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
	UseTet* Model;
public:
	TargetTet(Board* B);
	virtual ~TargetTet();
public:
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	void SetModel(UseTet* cur) { Model = cur; }
	void SetBoard(Board* GB) { m_GameBoard = GB; }
private:
	void SetColor(Tetromino::TET_TYPE Type);
	void SetTargetPos();
	void SetBodyByOrigin();
	bool CheckValidPos();
};

