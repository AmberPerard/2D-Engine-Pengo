#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

class BlockComponent : public dae::BaseComponent
{
public:
	BlockComponent(dae::GameObject* gameObject);
	~BlockComponent() override = default;
	BlockComponent(const BlockComponent& other) = delete;
	BlockComponent(BlockComponent&& other) noexcept = delete;
	BlockComponent& operator=(const BlockComponent& other) = delete;
	BlockComponent& operator=(BlockComponent&& other) noexcept = delete;

	void Update() override;
	void Render() override;
	void RenderUI() override;

	void HandleMovement();
	void EnableMovement(MovementDirection direction);
	void DisableMovement() { m_IsMovingBlock = false; }

	void MakeSpawnBlock(bool isSpawner);
	void SpawnFromBlock();
	bool IsSpawnBlock() const { return m_IsSpawnBlock; }

	void BreakBlock();

private:
	bool m_IsSpawnBlock{ false };
	bool m_IsMovingBlock{ false };

	MovementDirection m_MovementDirection { MovementDirection::NONE };
};
