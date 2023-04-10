#include "Keyboard.h"

Keyboard::Keyboard()
	:m_CurrentState(SDL_NUM_SCANCODES),
	m_PreviousState(SDL_NUM_SCANCODES),
	m_ButtonsPressedThisFrame(SDL_NUM_SCANCODES),
	m_ButtonsReleasedThisFrame(SDL_NUM_SCANCODES)
{
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i)
	{
		m_CurrentState[i] = 0;
		m_PreviousState[i] = 0;
		m_ButtonsPressedThisFrame[i] = 0;
		m_ButtonsReleasedThisFrame[i] = 0;
	}
}

void Keyboard::Update()
{
	SDL_PumpEvents();  // Updates keyboard state

	m_PreviousState = m_CurrentState;

	int numKeys{};
	const Uint8* state = SDL_GetKeyboardState(&numKeys);

	for (int i = 0; i < numKeys; ++i)
	{
		m_CurrentState[i] = state[i];
	}
}

bool Keyboard::IsButtonPressedThisFrame(SDL_Scancode key) const
{
	if (m_CurrentState[key] && !m_PreviousState[key])
	{
		return true;
	}
	return false;
}

bool Keyboard::IsButtonReleasedThisFrame(SDL_Scancode key) const
{
	if (!m_CurrentState[key] && m_PreviousState[key])
	{
		return true;
	}
	return false;
}

bool Keyboard::IsPressed(SDL_Scancode key) const
{
	return m_CurrentState[key];
}
