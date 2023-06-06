#include "BlockComponent.h"

#include "GameObject.h"
#include "RigidBody.h"

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
	if (!m_IsMovingBlock && !GetOwner()->GetComponent<dae::RigidBody>()) return;

	auto rigidBody = GetOwner()->GetComponent<dae::RigidBody>();

	switch (m_MovementDirection)
	{
	case UP:
		//move up
		rigidBody->Move({ 0,-1 });
		break;
	case DOWN:
		//move down
		rigidBody->Move({ 0,1 });
		break;
	case LEFT:
		//move left
		rigidBody->Move({ -1,0 });
		break;
	case RIGHT:
		//move right
		rigidBody->Move({ 1,0 });
		break;
	case NONE:
		//do nothing
		rigidBody->Move({ 0,0 });
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
