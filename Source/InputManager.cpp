#include "InputManager.h"

InputManager::InputManager()
{
	m_mouseX = 0;
	m_mouseY = 0;
	m_isGoingToQuit = false;
	m_isMouseUp = false;
}

void InputManager::UpdateInput()
{
	m_isMouseUp = false;
	SDL_Event mainEvent;
	m_mouseX = 0;
	m_mouseY = 0;
	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{
		case SDL_QUIT:
		{
			m_isGoingToQuit = true;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			m_isMouseUp = false;
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			m_isMouseUp = true;
			m_mouseX = mainEvent.motion.x;
			m_mouseY = mainEvent.motion.y;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

int InputManager::GetMouseX()
{
	return m_mouseX;
}

int InputManager::GetMouseY()
{
	return m_mouseY;
}

bool InputManager::IsGoingToQuit()
{
	return m_isGoingToQuit;
}

bool InputManager::IsMouseUp()
{
	return m_isMouseUp;
}
