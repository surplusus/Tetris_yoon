#pragma once
#include <vector>

class Tetromino
{
private:
	using VECTORTETRO = std::vector<POINT>;
	enum TETROMINO_TYPE { TETROMINO_I = 1, TETROMINO_J, 
		TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, 
		TETROMINO_Z };
	enum ROTATE_TYPE{POSE1 = 0 ,POSE2,POSE3,POSE4};
private:
	POINT _center;		// center point : base point of rotation
	VECTORTETRO _tetromino;	// vector of four monomino
	TETROMINO_TYPE _type = static_cast<TETROMINO_TYPE>(rand() % 7);
	ROTATE_TYPE _rotation = static_cast<ROTATE_TYPE>(rand()%4);
	bool life = true;
	COLORREF Color();
	void SetBody();		// make a pack of rectangle as tetromino body
public:
	Tetromino(TETROMINO_TYPE type, int x = 4, int y = 1);
public:
	bool Rotate();	// if able to rotate, return true
	void Move();
	void GoDown();
	bool checkValidPos();
};
