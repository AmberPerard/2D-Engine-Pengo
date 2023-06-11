#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"

namespace dae
{
	class ButtonComponent : public BaseComponent
	{
	public:
		ButtonComponent(GameObject* gameObject);
		~ButtonComponent() override = default;
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) = delete;


		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void RenderUI() override;

		virtual void OnClick() = 0;
		void SetSize(glm::vec2 Size);
	private:
		RenderComponent* m_pRenderComponent;
		glm::vec2 m_Size;
	};
}

