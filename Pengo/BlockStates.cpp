#include "BlockStates.h"

#include "RigidBody.h"

std::unique_ptr<dae::BaseState> WallIdleState::Update(dae::GameObject*)
{
	if (m_pBlockcomponent->IsMoving())
	{
		return std::make_unique<WallMovingState>();
	}
	return nullptr;
}

void WallIdleState::Enter(dae::GameObject* object)
{
	m_pBlockcomponent = object->GetComponent<BlockComponent>();
}

void WallIdleState::Exit(dae::GameObject*)
{

}

void WallIdleState::FixedUpdate(dae::GameObject*)
{
}

std::unique_ptr<dae::BaseState> WallMovingState::Update(dae::GameObject*)
{
	if (!m_pBlockcomponent->IsMoving())
	{
		return std::make_unique<WallIdleState>();
	}
	return nullptr;
}

void WallMovingState::Enter(dae::GameObject* object)
{
	m_pBlockcomponent = object->GetComponent<BlockComponent>();
}

void WallMovingState::Exit(dae::GameObject*)
{
}

void WallMovingState::FixedUpdate(dae::GameObject* object)
{
	if (!m_pBlockcomponent->IsMoving()) return;
	if(m_pBlockcomponent->IsStatic()) return;
	auto rigidBody = object->GetComponent<dae::RigidBody>();

	switch (m_pBlockcomponent->GetMovementDirection())
	{
	case UP:
		//move up
		object->GetTransform()->SetForwardVector(DirectionMap.at(UP));
		rigidBody->Move(DirectionMap.at(UP));
		break;
	case DOWN:
		//move down
		object->GetTransform()->SetForwardVector(DirectionMap.at(DOWN));
		rigidBody->Move(DirectionMap.at(DOWN));
		break;
	case LEFT:
		//move left
		object->GetTransform()->SetForwardVector(DirectionMap.at(LEFT));
		rigidBody->Move(DirectionMap.at(LEFT));
		break;
	case RIGHT:
		//move right
		object->GetTransform()->SetForwardVector(DirectionMap.at(RIGHT));
		rigidBody->Move(DirectionMap.at(RIGHT));
		break;
	case NONE:
		//do nothing
		object->GetTransform()->SetForwardVector(DirectionMap.at(NONE));
		rigidBody->Move(DirectionMap.at(NONE));
		break;
	}
}
