#pragma once
#include <memory>

#include "BaseComponent.h"
#include "CharacterComponent.h"

namespace dae
{
	class Subject;
	class Observer;
	class LivesDisplayComponent;

	class EnemyComponent  final : public CharacterComponent
	{
	public:
		EnemyComponent(GameObject* gameObject, LivesDisplayComponent* livesDisplay = nullptr);
		~EnemyComponent() override = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) noexcept = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		void Die() override;
		void GetCrushed();
		void GetHit();
	};
}
