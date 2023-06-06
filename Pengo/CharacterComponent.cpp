#include "CharacterComponent.h"

#include "Helpers.h"
#include "LivesDisplayComponent.h"
#include "Subject.h"

CharacterComponent::CharacterComponent(dae::GameObject* gameObject, dae::LivesDisplayComponent* livesDisplay)
	:BaseComponent(gameObject)
{
	m_CharacterSubject = std::make_unique<dae::Subject>();
	if (livesDisplay != nullptr)
	{
		m_CharacterSubject->AddObserver(livesDisplay);
	}
}

void CharacterComponent::Update()
{
}

void CharacterComponent::FixedUpdate()
{
}

void CharacterComponent::Render()
{
}

void CharacterComponent::RenderUI()
{
}

void CharacterComponent::Die()
{
	int lives = GetLives();
	SetLives(--lives);
	m_CharacterSubject->Notify(PLAYER_DIED, this->GetOwner());
	if (GetLives() < 0)
	{
		m_CharacterSubject->Notify(PLAYER_LOST, this->GetOwner());
	}
}

void CharacterComponent::GetCrushed()
{
	m_CharacterSubject->Notify(ENEMY_CRUSHED, this->GetOwner());
	if (GetLives() <= 0)
	{
		Die();
	}
}

void CharacterComponent::GetHit()
{
	m_CharacterSubject->Notify(ENEMY_HIT, this->GetOwner());
	if (GetLives() <= 0)
	{
		Die();
	}
}

void CharacterComponent::AddObserver(dae::Observer* observer)
{
	m_CharacterSubject->AddObserver(observer);
	Start();
}

void CharacterComponent::Start()
{
	m_CharacterSubject->Notify(LEVEL_STARTED, this->GetOwner());
}