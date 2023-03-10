#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Transform;

	class RotatorComponent final : public BaseComponent
	{
	public:
		RotatorComponent(GameObject* gameObject);
		~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update() override;
		void Render() override {};

		void SetRotationSpeed(float anglePerSecond) { m_AnglePerSec = anglePerSecond; };
	private:
		Transform* m_pTransform{nullptr};
		float m_AnglePerSec{ 45.0f };
	};
}

