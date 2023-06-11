#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

class EnemyComponent final : public dae::BaseComponent
{
public:
	EnemyComponent(dae::GameObject* gameObject);
	~EnemyComponent() override;
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) noexcept = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void RenderUI() override;

	void OnCollision(dae::GameObject* otherCollider);
	MovementDirection GetDirection() const { return m_CurrentDirection; }
	void SetDirection(MovementDirection direction) { m_CurrentDirection = direction; }

	void Start();
	void Die();
private:
	MovementDirection m_CurrentDirection;
};

