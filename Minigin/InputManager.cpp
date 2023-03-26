
#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include <SDL_syswm.h>
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	// Check controller keys
	UpdateConsoleInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void dae::InputManager::UpdateConsoleInput()
{
	for (auto& controller : m_Controllers)
	{
		controller->Update();
		for (auto& axisCommands : m_ConsoleAxis)
		{
			axisCommands.second->Execute();
		}

		for (auto& command : m_ConsoleCommands)
		{
			switch (command.first.first)
			{
			case State::Press:
				if (controller->IsButtonDownThisFrame(command.first.second))
				{
					command.second->Execute();
				}
				break;

			case State::Hold:
				if (controller->IsPressed(command.first.second))
				{
					command.second->Execute();
				}
				break;

			case State::Release:
				if (controller->IsButtonUpThisFrame(command.first.second))
				{
					command.second->Execute();
				}
				break;
			}
		}

	}
}

void dae::InputManager::AddController(int id)
{
	m_Controllers.push_back(std::make_unique<XController>(id));
}

dae::XController* dae::InputManager::GetController(int id) const
{
	//not good code i know that but i ran out of time sorry
	return m_Controllers.at(id).get();
}

