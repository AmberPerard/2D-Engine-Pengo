#pragma once

#include "BaseComponent.h"

namespace dae
{
	class TextComponent;

	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(GameObject* gameObject);
		~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		float getFPS() const { return m_fps; }
	private:
		float m_fps{};
		TextComponent* m_pTextComponent;
	};
}

