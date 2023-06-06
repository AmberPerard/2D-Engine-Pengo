#include "BlockComponent.h"

BlockComponent::BlockComponent(dae::GameObject* gameObject)
	:BaseComponent(gameObject)
{
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

void BlockComponent::HandleMovement()
{
	if (!m_IsMovingBlock) return;

	switch (m_MovementDirection)
	{
	case UP:
		//move up
		break;
	case DOWN:
		//move down
		break;
	case LEFT:
		//move left
		break;
	case RIGHT:
		//move right
		break;
	case NONE:
		//do nothing
		break;
	default:;
	}
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
