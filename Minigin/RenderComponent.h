#pragma once
#include <memory>
#include <string>

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(GameObject* gameObject);
		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void RenderUI() override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}

