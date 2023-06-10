#pragma once
#include <memory>

#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class BaseState;

	class StateMachine final : public BaseComponent
	{
	public:
		StateMachine(GameObject* gameObject);
		~StateMachine() override = default;
		StateMachine(const StateMachine& other) = delete;
		StateMachine(StateMachine&& other) = delete;
		StateMachine& operator=(const StateMachine& other) = delete;
		StateMachine& operator=(StateMachine&& other) = delete;

		void Initialize(std::unique_ptr<BaseState> startState);
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void RenderUI() override;

		void SetState(std::unique_ptr<BaseState> state);
	private:
		std::unique_ptr<BaseState> m_state;
	};
}
