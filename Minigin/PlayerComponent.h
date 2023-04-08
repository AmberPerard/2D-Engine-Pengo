#pragma once
#include <memory>

#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class LivesDisplayComponent;

	class PlayerComponent final : public BaseComponent
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

		int GetLives() const { return m_nrOfLives; }
		void AddObserver(Observer* observer) ;
		void Start();
		void Die();
	private:
		int m_nrOfLives{ 3 };
		int m_Score{ 0 };

		std::unique_ptr<Subject> m_PlayerSubject;

	};
}

