#pragma once
#include <string>

#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;

	class LivesDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		LivesDisplayComponent(GameObject* gameObject);
		~LivesDisplayComponent() override = default;
		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		void OnNotify(EventType event, GameObject* actor) override;

	private:
		TextComponent* pTextComponent;
		std::string m_text;
	};

}
