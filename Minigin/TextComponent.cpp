#include "TextComponent.h"

#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
	m_pRenderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
}

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
		if(m_pRenderComponent)
		{
			m_pRenderComponent->SetTexture(m_textTexture);
		}
	}
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::Render()
{
}

void dae::TextComponent::RenderUI()
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_font = std::move(font);
	m_needsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color color)
{
	m_color = color;
	m_needsUpdate = true;
}
