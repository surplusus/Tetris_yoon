#include "stdafx.h"
#include "Key.h"

void Key::SetKey(const WPARAM & wParam)
{
	if (wParam == VK_SPACE)
		m_Key[SPACE] = TRUE;
	if (wParam == VK_LEFT)
		m_Key[LEFT] = TRUE;
	if (wParam == VK_UP)
		m_Key[UP] = TRUE;
	if (wParam == VK_RIGHT)
		m_Key[RIGHT] = TRUE;
	if (wParam == VK_DOWN)
		m_Key[DOWN] = TRUE;
}

void Key::ClearKey()
{
	for (int i = 0; i < 5; ++i)
		m_Key[i] = false;
}
