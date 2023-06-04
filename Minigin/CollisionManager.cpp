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

void dae::CollisionManager::FixedUpdate()
{
	for (auto firstCollider : m_CollisionObjects)
	{
		for (auto secondCollider : m_CollisionObjects)
		{
			if (firstCollider == secondCollider)
			{
				continue;
			}
			if (CheckCollision(firstCollider, secondCollider))
			{
				firstCollider->OnCollision(secondCollider);
				secondCollider->OnCollision(firstCollider);
			}
		}
	}
}

bool dae::CollisionManager::CheckCollision(ColliderComponent* firstCollider, ColliderComponent* secondCollider)
{
	auto fPos = firstCollider->GetOwnerPosition();
	auto fSize = firstCollider->GetSize();
	auto sPos = secondCollider->GetOwnerPosition();
	auto sSize = secondCollider->GetSize();

	if((fPos.x +fSize.x) >= sPos.x &&
		fPos.x <= (sPos.x + sSize.x) &&
		(fPos.y + fSize.y) >= sPos.y &&
		fPos.y <= (sPos.y + sSize.y))
	{
				return true;
	}
	return false;
}
