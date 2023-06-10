#include "BlockComponent.h"

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
	HandleMovement();
}

void BlockComponent::Render()
{
}

void BlockComponent::RenderUI()
{
}

void BlockComponent::HandleMovement()
{
	if(m_IsStatic) return;
	if (!m_IsMovingBlock) return;
	//if(!GetOwner()->GetComponent<dae::RigidBody>()) return;

	auto rigidBody = GetOwner()->GetComponent<dae::RigidBody>();

	switch (m_MovementDirection)
	{
	case UP:
		//move up
		this->GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(UP));
		rigidBody->Move(DirectionMap.at(UP));
		break;
	case DOWN:
		//move down
		this->GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(DOWN));
		rigidBody->Move(DirectionMap.at(DOWN));
		break;
	case LEFT:
		//move left
		this->GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(LEFT));
		rigidBody->Move(DirectionMap.at(LEFT));
		break;
	case RIGHT:
		//move right
		this->GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(RIGHT));
		rigidBody->Move(DirectionMap.at(RIGHT));
		break;
	case NONE:
		//do nothing
		this->GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(NONE));
		rigidBody->Move(DirectionMap.at(NONE));
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

void BlockComponent::OnCollision(const dae::GameObject* collision)
{
	if(!m_IsMovingBlock)return;

	//other collider is a block or wall
	if(collision->GetComponent<BlockComponent>() != nullptr)
	{
		DisableMovement();
		auto offset = collision->GetComponent<dae::ColliderComponent>()->GetOffset();
		auto transform = GetOwner()->GetTransform();
		glm::vec2 lastDirection = transform->GetForwardVector();
		transform->SetPosition({ transform->GetLocalPosition().x + (( offset.x*2) * -(lastDirection.x)), transform->GetLocalPosition().y + (( offset.y*2) * -(lastDirection.y)) });
	}
}
