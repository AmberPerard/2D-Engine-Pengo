#pragma once
#include <memory>

#include "BaseComponent.h"

namespace dae
{
	class Subject;

	class PlayerComponent final : public dae::BaseComponent
	{
	public:
		PlayerComponent(GameObject* gameObject, GameObject* livesDisplay = nullptr);
		~PlayerComponent() override = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		int GetLives() const { return m_nrOfLives; };
		void Start();
		void Die();
	private:
		int m_nrOfLives{ 3 };
		int m_score{ 0 };

		//std::unique_ptr<Subject> m_PlayerSubject;

	};
}

