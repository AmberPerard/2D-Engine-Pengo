#pragma once
#include <memory>

#include "BaseComponent.h"
#include "CharacterComponent.h"
#include "Subject.h"

namespace dae
{
	class LivesDisplayComponent;

	class PlayerComponent final : public CharacterComponent
	{
	public:
		PlayerComponent(GameObject* gameObject, LivesDisplayComponent* livesDisplay = nullptr);
		~PlayerComponent() override = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		void Die() override;
	private:

	};
}

