#include "InputManager.h"

InputManager::InputManager()
{
	m_mouseX = 0;
	m_mouseY = 0;
	m_isGoingToQuit = false;
	m_isMouseClicked = false;
}

void InputManager::UpdateInput()
{
	m_isMouseClicked = false;
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
		case SDL_MOUSEBUTTONUP:
		{
			m_mouseX = mainEvent.motion.x;
			m_mouseY = mainEvent.motion.y;
			if (m_mouseX >= LEFT_EDGE && m_mouseX <= WINDOW_WIDTH - RIGHT_EDGE && m_mouseY >= TOP_EDGE && m_mouseY <= WINDOW_HEIGHT - BOTTOM_EDGE)
			{
				m_isMouseClicked = true;
			}

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

bool InputManager::IsMouseClick()
{
	return m_isMouseClicked;
}
