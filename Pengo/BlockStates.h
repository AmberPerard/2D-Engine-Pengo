#pragma once
#include "BaseState.h"
#include "BlockComponent.h"

class WallIdleState : public dae::BaseState
{
public:
	WallIdleState() = default;
	std::unique_ptr<BaseState> Update(dae::GameObject* object) override;
	void Enter(dae::GameObject* object) override;
	void Exit(dae::GameObject* object) override;
	void FixedUpdate(dae::GameObject* object) override;

private:
		BlockComponent* m_pBlockcomponent{};
};

class WallMovingState : public dae::BaseState
{
public:
	WallMovingState() = default;
	std::unique_ptr<BaseState> Update(dae::GameObject* object) override;
	void Enter(dae::GameObject* object) override;
	void Exit(dae::GameObject* object) override;
	void FixedUpdate(dae::GameObject* object) override;

private:
		BlockComponent* m_pBlockcomponent{};
};

class WallBreakingState : public dae::BaseState
{
public:
	WallBreakingState() = default;
	std::unique_ptr<BaseState> Update(dae::GameObject* object) override;
	void Enter(dae::GameObject* object) override;
	void Exit(dae::GameObject* object) override;
	void FixedUpdate(dae::GameObject* object) override;

private:
	BlockComponent* m_pBlockcomponent{};
};
