#pragma once
#include <vector>
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
	void ClearKey();
};

