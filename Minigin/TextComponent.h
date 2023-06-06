#pragma once
#include <memory>
#include <SDL_pixels.h>

#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
namespace dae
{
	class RenderComponent;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* gameObject);
		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void RenderUI() override;

		std::shared_ptr<Texture2D> GetTexture() { return m_textTexture; }
		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetColor(const SDL_Color color);
	private:
		bool m_needsUpdate = true;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		SDL_Color m_color {};
		std::shared_ptr<Texture2D> m_textTexture;
		RenderComponent* m_pRenderComponent;
	};
}
