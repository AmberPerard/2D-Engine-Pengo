#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{

	class RigidBody final : public BaseComponent
	{
	public:
		RigidBody(GameObject* gameObject, const glm::vec2& speed = { 50,50 });
		~RigidBody() override = default;
		RigidBody(const RigidBody& other) = delete;
		RigidBody(RigidBody&& other) noexcept = delete;
		RigidBody& operator=(const RigidBody& other) = delete;
		RigidBody& operator=(RigidBody&& other) noexcept = delete;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void RenderUI() override;

		void Move(const glm::vec2& moveVec);
		glm::vec2 GetMovementSpeed() const { return m_MovementSpeed; }
		glm::vec2 GetVelocity()const { return m_Velocity; }

	private:
		glm::vec2 m_MovementSpeed{};
		glm::vec2 m_Velocity{};
	};
}

