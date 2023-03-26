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

		template<typename T>
		void CreateControllerCommand(XController::ControllerButton button, State state, std::shared_ptr<GameObject> component);
		template<typename T>
		void CreateControllerAxis(XController::ControllerButton button, State state, std::shared_ptr<GameObject> component);
		void AddController(int id);
		XController* GetController(int id) const;

	private:
		void UpdateConsoleInput();

		using ControllerKey = std::pair<State, XController::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ConsoleCommands{};
		ControllerCommandsMap m_ConsoleAxis{};
		std::vector<std::unique_ptr<XController>> m_Controllers{};
	};

	template <typename T>
	void InputManager::CreateControllerCommand(XController::ControllerButton button, State state, std::shared_ptr<GameObject> component)
	{
		std::unique_ptr<T> command = std::make_unique<T>(component);
		ControllerKey keyThing = std::pair{ state,button };

		m_ConsoleCommands.insert(std::pair{ keyThing, std::move(command) });
	}

	template <typename T>
	void InputManager::CreateControllerAxis(XController::ControllerButton button, State state, std::shared_ptr<GameObject> component)
	{
		std::unique_ptr<T> command = std::make_unique<T>(component);
		ControllerKey keyThing = std::pair{ state,button };

		m_ConsoleAxis.insert(std::pair{ keyThing, std::move(command) });
	}
}
