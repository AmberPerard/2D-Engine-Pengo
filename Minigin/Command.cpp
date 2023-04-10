#include "Command.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Time.h"
#include <iostream>

#include "CharacterComponent.h"

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
	glm::vec3 actorPos = m_pActor->GetTransform()->GetLocalPosition();
	float actorPosX = actorPos.x + (m_Dir.x * Time::GetInstance().GetDeltaTime() * m_Speed);
	float actorPosY = actorPos.y + (m_Dir.y * Time::GetInstance().GetDeltaTime() * m_Speed);
	m_pActor->GetTransform()->SetPosition(actorPosX, actorPosY);
}

dae::Kill::Kill(std::shared_ptr<GameObject> pActor)
	:m_pActor(pActor)
{
}

void dae::Kill::Execute()
{
	m_pActor->GetComponent<dae::CharacterComponent>()->Die();
}

dae::CrushEnemy::CrushEnemy(std::shared_ptr<GameObject> pActor)
	:m_pActor(pActor)
{
}

void dae::CrushEnemy::Execute()
{
	m_pActor->GetComponent<dae::CharacterComponent>()->GetCrushed();
}

dae::HitEnemy::HitEnemy(std::shared_ptr<GameObject> pActor)
	:m_pActor(pActor)
	
{

}

void dae::HitEnemy::Execute()
{
	m_pActor->GetComponent<dae::CharacterComponent>()->GetHit();
}
