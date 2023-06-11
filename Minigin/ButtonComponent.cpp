#include "ButtonComponent.h"

#include <iostream>
#include <ostream>

#include "InputManager.h"

dae::ButtonComponent::ButtonComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{

	m_pRenderComponent = GetOwner()->GetComponent<RenderComponent>();
}

void dae::ButtonComponent::Update()
{
	const bool isMouseClicked = InputManager::GetInstance().IsMousePress();
	if (isMouseClicked)
	{
		const auto mousePos = InputManager::GetInstance().GetMousePos();
		float rWidth = 0;
		float rHeight = 0;
		if (m_pRenderComponent != nullptr)
		{
			rWidth = m_pRenderComponent->GetTextureSize().x;
			rHeight = m_pRenderComponent->GetTextureSize().y;
		}else
		{
			rWidth = m_Size.x;
			rHeight = m_Size.y;
		}
		const auto pos = GetOwner()->GetTransform()->GetLocalPosition();

		std::cout << "Mouse pos: " << mousePos.x << " " << mousePos.y << std::endl;
		bool one = pos.x <= mousePos.x;
		bool two = mousePos.x <= pos.x + rWidth;
		bool three = pos.y <= mousePos.y;
		bool four = mousePos.y <= pos.y + rHeight;

		if (one && two &&
			three && four)
			OnClick();
	}
}

void dae::ButtonComponent::FixedUpdate()
{
}

void dae::ButtonComponent::Render()
{
}

void dae::ButtonComponent::RenderUI()
{
}

void dae::ButtonComponent::SetSize(glm::vec2 Size)
{
	m_Size = Size;
}
