#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.h"
#include "Singleton.h"
#include "XController.h"
#include <SDL.h>

#include "Keyboard.h"

namespace dae
{
	enum class State
	{
		Hold,
		Press,
		Release
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		InputManager() = default;
		~InputManager() = default;
		bool ProcessInput();


		//controller stuff
		void CreateControllerCommand(XController::ControllerButton button, State state, std::unique_ptr<Command> command);
		int AddController();
		XController* GetController(int id) const;

		//keyboard stuff
		std::unique_ptr<Keyboard> m_Keyboard {std::make_unique<Keyboard>()};
		void CreateKeyboardCommand(SDL_KeyCode button, State state, std::unique_ptr<Command> command);
		void Clear();
	private:
		void UpdateConsoleInput();
		void UpdateKeyboardInput();

		using ControllerKey = std::pair<State, XController::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;

		using KeyboardKey = std::pair<State, SDL_Scancode>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		KeyboardCommandsMap m_KeyboardCommands{};

		ControllerCommandsMap m_ConsoleCommands{};
		std::vector<std::unique_ptr<XController>> m_Controllers{};
	};
}
