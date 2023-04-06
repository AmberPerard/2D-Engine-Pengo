#include "Command.h"

#include <iostream>
#include "GameObject.h"
#include "InputManager.h"
#include "Time.h"

dae::Command::Command()
{
}

dae::Move::Move(std::shared_ptr<GameObject> pActor, float speed, glm::vec2 dir, float acceleration)
	: m_pActor(pActor),
	m_Dir(dir),
	m_Speed(speed),
	m_Acceleration(acceleration)
{
}

void dae::Move::Execute()
{
	std::cout << "Move" << std::endl;
	glm::vec3 actorPos = m_pActor->GetTransform()->GetLocalPosition();
	float actorPosX = actorPos.x + (m_Dir.x * Time::GetInstance().GetDeltaTime() * m_Speed);
	float actorPosY = actorPos.y + (m_Dir.y * Time::GetInstance().GetDeltaTime() * m_Speed);
	m_pActor->GetTransform()->SetPosition(actorPosX, actorPosY);
}
