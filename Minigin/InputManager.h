#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.h"
#include "Singleton.h"
#include "XController.h"

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

		void CreateControllerCommand(XController::ControllerButton button, State state, std::unique_ptr<Command> command);
		void CreateControllerAxis(XController::ControllerButton button, State state, std::unique_ptr<Command> command);
		int AddController();
		XController* GetController(int id) const;

	private:
		void UpdateConsoleInput();

		using ControllerKey = std::pair<State, XController::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ConsoleCommands{};
		ControllerCommandsMap m_ConsoleAxis{};
		std::vector<std::unique_ptr<XController>> m_Controllers{};
	};
}
