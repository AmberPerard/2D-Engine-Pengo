#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::FixedUpdate()
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
			const auto& scale = transform->GetWorldScale();
			m_textureSize =  m_texture->GetSize();
			const float width = static_cast<float>(m_textureSize.x) * scale.x;
			const float height= static_cast<float>(m_textureSize.y) * scale.y;
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y,width,height);
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
	m_textureSize = m_texture->GetSize();
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_texture = texture;
	m_textureSize = m_texture->GetSize();
}
