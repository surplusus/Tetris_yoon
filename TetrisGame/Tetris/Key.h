#pragma once
#include <vector>
#include <iostream>
class Key
{
public:
	enum KEY_TYPE 
	{ SPACE = 0, LEFT, UP, RIGHT, DOWN };
private:
	std::vector<bool> m_Key;
public:
	Key() { 
		m_Key.resize(5); 
		ClearKey();
	}
	void SetKey(const WPARAM& wParam);
	const std::vector<bool> GetKey() const { return m_Key; }
	void ClearKey();
	bool operator[](KEY_TYPE index);
	
};

