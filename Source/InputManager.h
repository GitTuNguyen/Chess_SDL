#pragma once
#include "SDL.h"

class InputManager
{
public:
	InputManager();
	void UpdateInput();
	int GetMouseX();
	int GetMouseY();
	bool IsGoingToQuit();
	bool IsMouseUp();
private:
	int m_mouseX;
	int m_mouseY;
	bool m_isGoingToQuit;
	bool m_isMouseUp;
};