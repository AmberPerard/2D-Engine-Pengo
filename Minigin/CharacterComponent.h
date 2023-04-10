#pragma once
#include <memory>

#include "BaseComponent.h"

namespace dae
{
	class Subject;
	class Observer;
	class LivesDisplayComponent;

	class CharacterComponent : public dae::BaseComponent
	{
	public:
		CharacterComponent(dae::GameObject* gameObject, dae::LivesDisplayComponent* livesDisplay = nullptr);
		~CharacterComponent() override = default;
		CharacterComponent(const CharacterComponent& other) = delete;
		CharacterComponent(CharacterComponent&& other) noexcept = delete;
		CharacterComponent& operator=(const CharacterComponent& other) = delete;
		CharacterComponent& operator=(CharacterComponent&& other) noexcept = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		int GetLives() const { return m_NrOfLives; }
		void SetLives(int newLives) { m_NrOfLives = newLives; }
		int GetScore() const { return m_Score; }
		void SetScore(int newScore) { m_Score = newScore; }

		void AddObserver(dae::Observer* observer);
		void Start();
		virtual void Die() = 0;
		std::unique_ptr<dae::Subject> m_CharacterSubject;

	private:
		int m_NrOfLives{ 3 };
		int m_Score{ 0 };


	};
}