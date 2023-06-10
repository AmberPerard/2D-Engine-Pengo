#include "BlockComponent.h"

#include <iostream>

#include "ColliderComponent.h"
#include "GameInfo.h"
#include "GameObject.h"
#include "RigidBody.h"

BlockComponent::BlockComponent(dae::GameObject* gameObject)
	:BaseComponent(gameObject)
{
	if (GetOwner()->GetComponent<dae::ColliderComponent>())
	{
		dae::ColliderComponent::CollisionCallback callback = [&](dae::GameObject* hit) { this->OnCollision(hit); };
		GetOwner()->GetComponent<dae::ColliderComponent>()->SetCollisionCallback(callback);
	}

}

void BlockComponent::Update()
{
}

void BlockComponent::FixedUpdate()
{
}

void BlockComponent::Render()
{
}

void BlockComponent::RenderUI()
{
}

void BlockComponent::EnableMovement(MovementDirection direction)
{
	m_IsMovingBlock = true;
	m_MovementDirection = direction;
}

void BlockComponent::MakeSpawnBlock(bool isSpawner)
{
	m_IsSpawnBlock = isSpawner;
}

void BlockComponent::SpawnFromBlock()
{
	if (m_IsSpawnBlock)
	{
		//spawn an enemy
	}
}

void BlockComponent::BreakBlock()
{
	//set the state to being broken
}

void BlockComponent::OnCollision(const dae::GameObject* collision)
{
	if(!m_IsMovingBlock)return;

	//other collider is a block or wall
	auto otherBlockComp = collision->GetComponent<BlockComponent>();
	if(otherBlockComp != nullptr)
	{
		DisableMovement();
		glm::vec2 lastDirection = GetOwner()->GetTransform()->GetForwardVector();
		const auto otherCol = otherBlockComp->GetColumn();
		const auto otherRow = otherBlockComp->GetRow();

		const auto newCol = otherCol + (1 * -int(lastDirection.x));
		const auto newRow = otherRow + (1 * -int(lastDirection.y));

		const auto newPosX = newCol * GameInfo::GetInstance().GetBlockSize().x + GameInfo::GetInstance().GetPlayFieldOffset().x;
		const auto newPosY = newRow * GameInfo::GetInstance().GetBlockSize().y + GameInfo::GetInstance().GetPlayFieldOffset().y;

		GetOwner()->GetTransform()->SetPosition(glm::vec2{ newPosX,newPosY });
		m_Row = newRow;
		m_Col = newCol;
	}
}
