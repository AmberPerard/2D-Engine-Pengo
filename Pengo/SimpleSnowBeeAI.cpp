#include "SimpleSnowBeeAI.h"

#include "GameObject.h"

SimpleSnowBeeAI::SimpleSnowBeeAI(dae::GameObject* gameObject)
	:BaseComponent(gameObject)
{
	auto rigidBody = GetOwner()->GetComponent<dae::RigidBody>();
	if (rigidBody != nullptr)
	{
		m_RigidBody = rigidBody;
	}

	auto enemyComponent = GetOwner()->GetComponent<EnemyComponent>();
	if (enemyComponent != nullptr)
	{
		m_EnemyComponent = enemyComponent;
	}
}

void SimpleSnowBeeAI::Update()
{
	if (m_EnemyComponent == nullptr)
		return;

	switch (m_EnemyComponent->GetDirection())
	{
	case UP:
		GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(UP));
		m_RigidBody->Move(DirectionMap.at(UP));
		break;
	case DOWN:
		GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(DOWN));
		m_RigidBody->Move(DirectionMap.at(DOWN));
		break;
	case LEFT:
		GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(LEFT));
		m_RigidBody->Move(DirectionMap.at(LEFT));
		break;
	case RIGHT:
		GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(RIGHT));
		m_RigidBody->Move(DirectionMap.at(RIGHT));
		break;
	case NONE:
		GetOwner()->GetTransform()->SetForwardVector(DirectionMap.at(NONE));
		m_RigidBody->Move(DirectionMap.at(NONE));
		break;
	}
}

void SimpleSnowBeeAI::FixedUpdate()
{
}

void SimpleSnowBeeAI::Render()
{
}

void SimpleSnowBeeAI::RenderUI()
{
}
