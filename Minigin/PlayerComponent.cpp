#include "PlayerComponent.h"

#include "LivesDisplayComponent.h"
#include "Subject.h"
#include "Observer.h"

dae::PlayerComponent::PlayerComponent(GameObject* gameObject, LivesDisplayComponent* livesDisplay)
	:BaseComponent(gameObject)
{
	m_PlayerSubject = std::make_unique<Subject>();
	if (livesDisplay != nullptr)
	{
		m_PlayerSubject->AddObserver(livesDisplay);
	}
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

void dae::PlayerComponent::AddObserver(Observer* observer)
{
	m_PlayerSubject->AddObserver(observer);
	Start();
}

void dae::PlayerComponent::Start()
{
	m_PlayerSubject->Notify(PLAYED_DIED, this->GetOwner());
}

void dae::PlayerComponent::Die()
{
	m_nrOfLives--;
	m_PlayerSubject->Notify(PLAYED_DIED, this->GetOwner());
	if (m_nrOfLives < 0)
	{
		//m_PlayerSubject->Notify(PLAYED_LOST, this->GetOwner());
	}
}
