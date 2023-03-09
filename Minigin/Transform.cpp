#include "Transform.h"

void dae::Transform::SetPosition(float x, float y)
{
	SetPosition(x, y, 0);
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

dae::Transform::Transform(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::Transform::Update()
{
}

void dae::Transform::Render()
{
}
