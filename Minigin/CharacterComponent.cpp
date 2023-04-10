#include "CharacterComponent.h"

#include "LivesDisplayComponent.h"
#include "Subject.h"

dae::CharacterComponent::CharacterComponent(dae::GameObject* gameObject, dae::LivesDisplayComponent* livesDisplay)
	:BaseComponent(gameObject)
{
	m_CharacterSubject = std::make_unique<Subject>();
	if (livesDisplay != nullptr)
	{
		m_CharacterSubject->AddObserver(livesDisplay);
	}
}

void dae::CharacterComponent::Update()
{
}

void dae::CharacterComponent::Render()
{
}

void dae::CharacterComponent::RenderUI()
{
}

void dae::CharacterComponent::AddObserver(dae::Observer* observer)
{
	m_CharacterSubject->AddObserver(observer);
	Start();
}

void dae::CharacterComponent::Start()
{
	m_CharacterSubject->Notify(LEVEL_STARTED, this->GetOwner());
}