#include "CollisionManager.h"

void dae::CollisionManager::Add(ColliderComponent* colliderComponent)
{
	//No duplicates
	auto it = std::find(m_CollisionObjects.begin(), m_CollisionObjects.end(), colliderComponent);
	if (it == m_CollisionObjects.end())
	{
		m_CollisionObjects.push_back(colliderComponent);
	}
}

void dae::CollisionManager::Remove(ColliderComponent* colliderComponent)
{
	//If it exists, remove it
	auto it = std::find(m_CollisionObjects.begin(), m_CollisionObjects.end(), colliderComponent);
	if (it != m_CollisionObjects.end())
	{
		m_CollisionObjects.erase(it);
	}
}

void dae::CollisionManager::UpdateCollision()
{
	for (auto firstCollider : m_CollisionObjects)
	{
		for (auto secondCollider : m_CollisionObjects)
		{
			if (firstCollider == secondCollider)
			{
				continue;
			}
			CheckCollision(firstCollider, secondCollider);

		}
	}
}

bool dae::CollisionManager::CheckCollision(ColliderComponent* firstCollider, ColliderComponent* secondCollider)
{
	auto firstColliderPos = firstCollider->GetOwnerPosition();
	auto firtColliderSize = firstCollider->GetSize();
	auto secondColliderPos = secondCollider->GetOwnerPosition();
	auto secondColliderSize = secondCollider->GetSize();

	if ((firstColliderPos.x + firtColliderSize.x) < secondColliderPos.x || (secondColliderPos.x + secondColliderSize.x) < firstColliderPos.x)
	{
		return false;
	}

	if (firstColliderPos.y > (secondColliderPos.y + secondColliderSize.y) || secondColliderPos.y > (firstColliderPos.y + firtColliderSize.y))
	{
		return false;
	}

	return true;
}
