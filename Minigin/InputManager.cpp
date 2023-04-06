
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	// Check controller keys
	UpdateConsoleInput();
	UpdateKeyboardInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void dae::InputManager::CreateControllerCommand(XController::ControllerButton button, State state, std::unique_ptr<Command> command)
{
	ControllerKey keyThing = std::pair{ state,button };
	m_ConsoleCommands.insert(std::pair{ keyThing, std::move(command) });
}

void dae::InputManager::UpdateConsoleInput()
{
	for (auto& controller : m_Controllers)
	{
		controller->Update();

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

void dae::InputManager::UpdateKeyboardInput()
{
	for (auto& command : m_KeyboardCommands)
	{
		switch (command.first.first)
		{
		case State::Press:
			if (SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(command.first.second)])
			{
				command.second->Execute();
			}
			break;
		case State::Hold:
			if (SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(command.first.second)])
			{
				command.second->Execute();
			}
			break;
		case State::Release:
			if (SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(command.first.second)])
			{
				command.second->Execute();
			}
			break;
		}
	}
}

int dae::InputManager::AddController()
{
	m_Controllers.push_back(std::make_unique<XController>((int)m_Controllers.size()));
	return (int)m_Controllers.size() - 1;
}

dae::XController* dae::InputManager::GetController(int id) const
{
	//not good code i know that but i ran out of time sorry
	return m_Controllers.at(id).get();
}

void dae::InputManager::CreateKeyboardCommand(SDL_KeyCode button, State state, std::unique_ptr<Command> command)
{
	KeyboardKey keyThing = std::pair{ state,button };
	m_KeyboardCommands.insert(std::pair{ keyThing, std::move(command) });
}

