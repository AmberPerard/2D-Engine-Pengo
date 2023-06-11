#pragma once
#include "BaseState.h"

class PlayerState : dae::BaseState
{
public:
	std::unique_ptr<BaseState> Update(dae::GameObject* object) override;
	void FixedUpdate(dae::GameObject* object) override;
	void Enter(dae::GameObject* object) override;
	void Exit(dae::GameObject* object) override;
};

