#pragma once
#include "Background.h"
#include <vector>

class Tetromino
{
public:
	enum TETROMINO_TYPE {
		TETROMINO_I = 1, TETROMINO_J,
		TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T,
		TETROMINO_Z
	};
private:
	using VECTORTETRO = std::vector<POINT>;
	enum KEY_TYPE { SPACE = 0, LEFT = 1, UP, RIGHT, DOWN };
	enum ROTATE_TYPE { POSE1 = 0, POSE2, POSE3, POSE4 };
	const int boardHeight = 15;
public:
	Tetromino(int x = 4, int y = 0,
		TETROMINO_TYPE type = static_cast<TETROMINO_TYPE>(rand() % 7));
private:
	POINT _center;			// center point : base point of rotation
	VECTORTETRO _body;		// body based on center pos
	VECTORTETRO _tetromino;	// origin form four monomino block
	VECTORTETRO _predict;	// predict tetromino when IsBlockOnEnd()
	TETROMINO_TYPE _type;
	ROTATE_TYPE _rotation = static_cast<ROTATE_TYPE>(rand() % 4);
	bool life = true;
	Background* _background;
public:
	void SetTetromino();		// make a pack of rectangle as tetromino body
	void SetBackground(Background* BG) { _background = BG; }
	bool Rotate();	// if able to rotate, return true
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void GoStrightDown();
	bool CheckValidPos();
public:
	void Update(Background* BG);
	bool IsBlockOnEnd();
	void SetCenter(POINT cen) { _center = cen; }
	void SetBody(POINT center);
	void SetPredict();
	const POINT GetCenter() const { return _center; }
	const VECTORTETRO& GetBody() const { return _body; }
	const VECTORTETRO& GetPredict() const { return _predict; }
	const TETROMINO_TYPE& GetType() const { return _type;}
};

