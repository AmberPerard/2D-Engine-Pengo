#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <SDL_syswm.h>

#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisGame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	//SDL_Event e;
	//while (SDL_PollEvent(&e)) {
	//	if (e.type == SDL_QUIT) {
	//		return false;
	//	}
	//	if (e.type == SDL_KEYDOWN) {
	//		
	//	}
	//	if (e.type == SDL_MOUSEBUTTONDOWN) {
	//		
	//	}
	//	// etc...

	//	//process event for IMGUI
	//	ImGui_ImplSDL2_ProcessEvent(&e);
	//}
	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &m_CurrentState);

	if (dwResult == ERROR_SUCCESS)
	{
		std::cout << "controller is connected";
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}

	return true;
}

bool dae::InputManager::IsButtonDownThisFrame(unsigned button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::InputManager::IsButtonUpThisFrame(unsigned button) const
{
	return m_ButtonsReleasedThisGame & button;
}

bool dae::InputManager::IsPressed(unsigned button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}
