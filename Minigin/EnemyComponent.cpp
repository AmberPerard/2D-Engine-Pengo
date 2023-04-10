#include "EnemyComponent.h"

#include "LivesDisplayComponent.h"
#include "Subject.h"
#include "Observer.h"
dae::EnemyComponent::EnemyComponent(GameObject* gameObject, LivesDisplayComponent* livesDisplay)
	:CharacterComponent(gameObject, livesDisplay)
{
}

void dae::EnemyComponent::Update()
{
}

void dae::EnemyComponent::Render()
{
}

void dae::EnemyComponent::RenderUI()
{
}

void dae::EnemyComponent::Die()
{
	if (GetLives() <= 0)
	{
		m_CharacterSubject->Notify(ENEMY_DIED, this->GetOwner());
	}
}

void dae::EnemyComponent::GetCrushed()
{
	int lives = GetLives();
	SetLives(--lives);
	m_CharacterSubject->Notify(ENEMY_CRUSHED, this->GetOwner());
	if (GetLives() <= 0)
	{
		Die();
	}
}

void dae::EnemyComponent::GetHit()
{
	int lives = GetLives();
	SetLives(--lives);
	m_CharacterSubject->Notify(ENEMY_HIT, this->GetOwner());
	if (GetLives() <= 0)
	{
		Die();
	}
}