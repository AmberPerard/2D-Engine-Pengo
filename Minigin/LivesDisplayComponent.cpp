#include "LivesDisplayComponent.h"

#include "PlayerComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Observer.h"

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* gameObject)
	:BaseComponent(gameObject),m_text("Lives: 3")
{
	pTextComponent = gameObject->GetComponent<TextComponent>();
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

void dae::LivesDisplayComponent::OnNotify(EventType event, GameObject* actor)
{
	switch (event)
	{
		case PLAYER_DIED:
		m_text = "Lives: " + std::to_string(actor->GetComponent<CharacterComponent>()->GetLives());
		pTextComponent->SetText(m_text);
		break;
	default: ;
	}
}
