#include "Command.h"

#include <iostream>

#include "ControllerComponent.h"
#include "GameObject.h"
#include "InputManager.h"

dae::Command::Command()
{
}

dae::Move::Move(std::shared_ptr<GameObject> pActor, float speed, float acceleration)
	: m_pActor(pActor),
	m_Speed(speed),
	m_Acceleration(acceleration)
{
}

void dae::Move::Execute()
{
	const int controllerId = m_pActor->GetComponent<ControllerComponent>()->GetContollerID();
	glm::vec2 moveInput = InputManager::GetInstance().GetController(controllerId)->GetLeftThumbStick();
	glm::vec3 actorPos = m_pActor->GetTransform()->GetLocalPosition();
	float actorPosX = actorPos.x + moveInput.x;
	float actorPosY = actorPos.y + moveInput.y;
	m_pActor->GetTransform()->SetPosition(actorPosX, actorPosY);
}
