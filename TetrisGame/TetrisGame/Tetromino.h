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
	using KEYVECTOR = std::vector<bool>;
	enum KEY_TYPE { SPACE = 0, LEFT = 1, UP, RIGHT, DOWN };
	enum ROTATE_TYPE { POSE1 = 0, POSE2, POSE3, POSE4 };
public:
	Tetromino(int x = 4, int y = 1,
		TETROMINO_TYPE type = static_cast<TETROMINO_TYPE>(rand() % 7));
private:
	POINT _center;		// center point : base point of rotation
	VECTORTETRO _tetromino;	// = body : vector of four monomino
	TETROMINO_TYPE _type;
	ROTATE_TYPE _rotation = static_cast<ROTATE_TYPE>(rand() % 4);
	bool life = true;
	Background* _background;
private:
	void SetBody();		// make a pack of rectangle as tetromino body
	void SetBackground(Background* BG) { _background = BG; }
	bool Rotate();	// if able to rotate, return true
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void GoStrightDown();
	bool CheckValidPos();
public:
	void Update(KEYVECTOR &key, Background* BG);
	bool IsBlockOnEnd();
	const POINT GetCenter() const { return _center; }
	const VECTORTETRO& GetTetroBody() const { return _tetromino; }
	const TETROMINO_TYPE& GetType() const {return _type;}
};

