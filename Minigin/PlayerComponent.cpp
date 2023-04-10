#include "PlayerComponent.h"

#include "LivesDisplayComponent.h"
#include "Subject.h"
#include "Observer.h"

dae::PlayerComponent::PlayerComponent(GameObject* gameObject, LivesDisplayComponent* livesDisplay)
	:CharacterComponent(gameObject,livesDisplay)
{
}

void dae::PlayerComponent::Update()
{
}

void dae::PlayerComponent::Render()
{
}

void dae::PlayerComponent::RenderUI()
{
}

void dae::PlayerComponent::Die()
{
	int lives = GetLives();
	SetLives(--lives);
	m_CharacterSubject->Notify(PLAYER_DIED, this->GetOwner());
	if (GetLives() < 0)
	{
		m_CharacterSubject->Notify(PLAYER_LOST, this->GetOwner());
	}
}
