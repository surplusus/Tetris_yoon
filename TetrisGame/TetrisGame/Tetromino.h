#pragma once
#include "Background.h"
#include <vector>

class Tetromino
{
private:
	using KEYVECTOR = std::vector<bool>;
	enum KEY_TYPE { SPACE=0, LEFT=1, UP, RIGHT, DOWN };
	using VECTORTETRO = std::vector<POINT>;
	enum TETROMINO_TYPE { TETROMINO_I = 1, TETROMINO_J, 
		TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, 
		TETROMINO_Z };
	enum ROTATE_TYPE{POSE1 = 0 ,POSE2,POSE3,POSE4};
public:
	Tetromino(TETROMINO_TYPE type = static_cast<TETROMINO_TYPE>(rand() % 7)
		, int x = 4, int y = 1);
private:
	POINT _center;		// center point : base point of rotation
	VECTORTETRO _tetromino;	// vector of four monomino
	TETROMINO_TYPE _type;
	ROTATE_TYPE _rotation = static_cast<ROTATE_TYPE>(rand()%4);
	bool life = true;

private:
	COLORREF Color();
	void SetBody();		// make a pack of rectangle as tetromino body
	bool Rotate(KEY_TYPE key);	// if able to rotate, return true
	void Move();
	void GoDown();
	bool CheckValidPos();
	// check each block
private:
	void IsBlockOn(POINT block);
public:
	const Background& GetBoard(Background &gameboard) const { return gameboard; }
	void KeyInput(KEYVECTOR &key);
	void Update();
};

