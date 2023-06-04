#include "ColliderComponent.h"

#include "CollisionManager.h"

dae::ColliderComponent::ColliderComponent(GameObject* pGameObject, glm::vec2 pos, glm::vec2 size)
	:BaseComponent(pGameObject),
	m_Size(size)

{
	CollisionManager::GetInstance().Add(this);
}

dae::ColliderComponent::~ColliderComponent()
{
	CollisionManager::GetInstance().Remove(this);
}

void dae::ColliderComponent::Update()
{
}

void dae::ColliderComponent::Render()
{
}

void dae::ColliderComponent::RenderUI()
{
}

glm::vec3 dae::ColliderComponent::GetOwnerPosition() const
{
	return this->GetOwner()->GetTransform()->GetWorldPosition();
}

void dae::ColliderComponent::OnCollision(ColliderComponent* other)
{
	if (m_CollisionCallback)
	{
		m_CollisionCallback(other->GetOwner());
	}
}
