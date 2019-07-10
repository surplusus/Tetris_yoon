#pragma once
#include "Object.h"
#include "Block.h"
#include <vector>
#include <ctime>
class Board;

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
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	std::vector<Block*> GetOrigin(Tetromino::TET_TYPE type);
	void SetOrigin();
	
};

class UseTet : public Tetromino
{
public:
	UseTet(Board* B);
	virtual ~UseTet() {}
private:
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
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
	void InputKey(const std::vector<bool>* key);
public:
	const TET_TYPE GetType() const { return m_Type; }
	virtual void Init();
	virtual void Update(const std::vector<bool>* key);
	virtual void Draw();
};


class TargetTet : public Tetromino
{
private:
	POINT m_CenPos;
	TET_TYPE m_Type;
	Board* m_GameBoard;
public:
	TargetTet(Board* B);
	virtual ~TargetTet() {}
public:
	std::vector<Block*> m_Body;	// body = printer to Origin, movo to center
public:
	//virtual void Init() {}	//	¾È¾²´Â ³ð
	virtual void Init(UseTet* cur);
	virtual void Update();
	virtual void Draw();
private:
	void SetColor(Tetromino::TET_TYPE Type);
	void SetTargetPoint();
	void SetBodyByOrigin();

};

