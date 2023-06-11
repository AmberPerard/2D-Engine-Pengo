#pragma once
#include "BaseComponent.h"
#include "EnemyComponent.h"
#include "RigidBody.h"

class SimpleSnowBeeAI final : public dae::BaseComponent
{
public:
	SimpleSnowBeeAI(dae::GameObject* gameObject);
	~SimpleSnowBeeAI() override = default;
	SimpleSnowBeeAI(const SimpleSnowBeeAI& other) = delete;
	SimpleSnowBeeAI(SimpleSnowBeeAI&& other) noexcept = delete;
	SimpleSnowBeeAI& operator=(const SimpleSnowBeeAI& other) = delete;
	SimpleSnowBeeAI& operator=(SimpleSnowBeeAI&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void RenderUI() override;
private:
	EnemyComponent* m_EnemyComponent;
	dae::RigidBody* m_RigidBody;
};


