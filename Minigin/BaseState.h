#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseState
	{
	public:
		virtual ~BaseState() = default;
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete;
		virtual std::unique_ptr<BaseState> Update(GameObject* object) = 0;
		virtual void Enter(GameObject* object) = 0;
		virtual void Exit(GameObject* object) = 0;
	};
}

