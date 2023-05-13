#include "GameCommands.h"

#include "CharacterComponent.h"
#include "GameTime.h"

Move::Move(std::shared_ptr<dae::GameObject> pActor, float speed, glm::vec2 dir, float acceleration)
	: m_pActor(pActor),
	m_Dir(dir),
	m_Speed(speed),
	m_Acceleration(acceleration)
{
}

void Move::Execute()
{
	glm::vec3 actorPos = m_pActor->GetTransform()->GetLocalPosition();
	float actorPosX = actorPos.x + (m_Dir.x * GameTime::GetInstance().GetDeltaTime() * m_Speed);
	float actorPosY = actorPos.y + (m_Dir.y * GameTime::GetInstance().GetDeltaTime() * m_Speed);
	m_pActor->GetTransform()->SetPosition(actorPosX, actorPosY);
}

Kill::Kill(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)
{
}

void Kill::Execute()
{
	m_pActor->GetComponent<CharacterComponent>()->Die();
}

CrushEnemy::CrushEnemy(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)
{
}

void CrushEnemy::Execute()
{
	m_pActor->GetComponent<CharacterComponent>()->GetCrushed();
}

HitEnemy::HitEnemy(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)

{

}

void HitEnemy::Execute()
{
	m_pActor->GetComponent<CharacterComponent>()->GetHit();
}