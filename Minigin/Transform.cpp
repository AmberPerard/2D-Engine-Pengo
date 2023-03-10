#include "Transform.h"

#include "GameObject.h"

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

void dae::Transform::UpdateWorldPos()
{
	if (m_isDirty)
	{
		if (m_parent != nullptr)
		{
			m_worldPosition = m_parent->GetWorldPosition() + GetLocalPosition();
		}
		else
		{
			m_worldPosition = m_localPosition;
		}
	}
	m_isDirty = false;
}

void dae::Transform::SetPosition(float x, float y)
{
	SetPosition(x, y, 0);
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
	SetDirty();
}

void dae::Transform::SetPosition(glm::vec3 pos)
{
	m_localPosition = pos;
	SetDirty();
}

glm::vec3 dae::Transform::GetWorldPosition()
{
	if (m_isDirty)
	{
		UpdateWorldPos();
	}
	return m_worldPosition;
}

void dae::Transform::SetParent(Transform* gameObject)
{
	m_parent = gameObject;
}
