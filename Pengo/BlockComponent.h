#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Helpers.h"

class BlockComponent : public dae::BaseComponent
{
public:
	BlockComponent(dae::GameObject* gameObject);
	~BlockComponent() override;
	BlockComponent(const BlockComponent& other) = delete;
	BlockComponent(BlockComponent&& other) noexcept = delete;
	BlockComponent& operator=(const BlockComponent& other) = delete;
	BlockComponent& operator=(BlockComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void RenderUI() override;

	void EnableMovement(MovementDirection direction);
	void DisableMovement() { m_IsMovingBlock = false; }
	bool IsMoving() const { return m_IsMovingBlock; }
	MovementDirection GetMovementDirection() const { return m_MovementDirection; }

	void MakeSpawnBlock(bool isSpawner);
	void SpawnFromBlock();
	bool IsSpawnBlock() const { return m_IsSpawnBlock; }

	void BreakBlock();
	void SetStatic(bool isStatic) { m_IsStatic = isStatic; }
	bool IsStatic() const { return m_IsStatic; }

	glm::vec2 GetPosition() const { return this->GetOwner()->GetTransform()->GetWorldPosition(); }

	void OnCollision(const dae::GameObject* collision);

	int GetRow() const { return m_Row; }
	int GetColumn() const { return m_Col; }
	void SetRow(int row) { m_Row = row; }
	void SetColumn(int col) { m_Col = col; }

private:
	bool m_IsSpawnBlock{ false };
	bool m_IsMovingBlock{ false };
	bool m_IsStatic{ false };

	int m_Row{ 0 };
	int m_Col{ 0 };

	MovementDirection m_MovementDirection{ MovementDirection::NONE };
};
