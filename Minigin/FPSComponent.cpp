#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
	m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void dae::FPSComponent::Update()
{
	m_fps = 1 / Time::GetInstance().GetDeltaTime();
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText(std::to_string(int(m_fps)) + " FPS");
	}
}

void dae::FPSComponent::Render()
{
}

void dae::FPSComponent::RenderUI()
{
}
