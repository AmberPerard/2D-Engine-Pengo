#include "Transform.h"

#include "GameObject.h"

dae::Transform::Transform(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}


void dae::Transform::Update()
{
}

void dae::Transform::FixedUpdate()
{
}

void dae::Transform::Render()
{
}

void dae::Transform::RenderUI()
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


void dae::Transform::SetPosition(glm::vec2 pos)
{
	m_localPosition = pos;
	SetDirty();
}

void dae::Transform::SetScale(float scale)
{
	SetScale({ scale, scale });
}

void dae::Transform::SetScale(glm::vec2 pos)
{
	m_localScale = pos;
	SetDirtyScale();
}

glm::vec2 dae::Transform::GetWorldPosition()
{
	if (m_isDirty)
	{
		UpdateWorldPos();
	}
	return m_worldPosition;
}

glm::vec2 dae::Transform::GetWorldScale()
{
	if (m_isScaleDirty)
	{
		UpdateWorldScale();
	}
	return m_worldScale;
}

void dae::Transform::UpdateWorldScale()
{
	if (m_isScaleDirty)
	{
		if (m_parent != nullptr)
		{
			m_worldScale = m_parent->GetWorldScale() * GetLocalScale();
		}
		else
		{
			m_worldScale = m_localScale;
		}
	}
	m_isScaleDirty = false;
}

void dae::Transform::SetParent(Transform* gameObject)
{
	m_parent = gameObject;
}
