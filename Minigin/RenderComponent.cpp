#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render()
{
	if (m_texture != nullptr)
	{
		const auto transform = GetOwner()->GetTransform();
		if (transform != nullptr)
		{
			const auto& pos = transform->GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}else
		{
			Renderer::GetInstance().RenderTexture(*m_texture, 0, 0);
		}
	}
}

void dae::RenderComponent::RenderUI()
{
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
}
