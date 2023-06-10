#include "RigidBody.h"
#include "GameObject.h"
#include "GameTime.h"

dae::RigidBody::RigidBody(GameObject* gameObject, const glm::vec2& speed)
	:BaseComponent(gameObject),
	m_MovementSpeed(speed)
{
}

void dae::RigidBody::Update()
{
}

void dae::RigidBody::FixedUpdate()
{
}

void dae::RigidBody::Render()
{
}

void dae::RigidBody::RenderUI()
{
}

void dae::RigidBody::Move(const glm::vec2& moveVec)
{
	if (moveVec != glm::vec2{0, 0})
	{
		m_Velocity.x = moveVec.x * GameTime::GetInstance().GetDeltaTime() * m_MovementSpeed.x;
		m_Velocity.y = moveVec.y * GameTime::GetInstance().GetDeltaTime() * m_MovementSpeed.y;

		auto newPos = GetOwner()->GetTransform()->GetLocalPosition();
		newPos.x += m_Velocity.x;
		newPos.y += m_Velocity.y;

		GetOwner()->GetTransform()->SetPosition({ newPos.x, newPos.y });
	}
}
