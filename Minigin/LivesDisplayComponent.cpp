#include "LivesDisplayComponent.h"

#include "PlayerComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Observer.h"

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::LivesDisplayComponent::Update()
{
}

void dae::LivesDisplayComponent::Render()
{
}

void dae::LivesDisplayComponent::RenderUI()
{
}

void dae::LivesDisplayComponent::OnNotify(Event event, GameObject* actor)
{
	switch (event.m_type)
	{
		case PLAYED_DIED:
		m_text = "Lives: " + std::to_string(actor->GetComponent<PlayerComponent>()->GetLives());
		pTextComponent->SetText(m_text);
		break;
	default: ;
	}
}
