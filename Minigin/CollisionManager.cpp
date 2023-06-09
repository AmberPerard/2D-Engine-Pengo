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
	auto fOffset = firstCollider->GetOffset();
	auto fSize = firstCollider->GetSize();
	auto sPos = secondCollider->GetOwnerPosition();
	auto sOffset = firstCollider->GetOffset();
	auto sSize = secondCollider->GetSize();

	if((fPos.x - fOffset.x +fSize.x) >= sPos.x + sOffset.x &&
		fPos.x + fOffset.x <= (sPos.x - sOffset.x + sSize.x) &&
		(fPos.y - fOffset.y + fSize.y) >= sPos.y + sOffset.y &&
		fPos.y + fOffset.y <= (sPos.y - sOffset. y + sSize.y))
	{
				return true;
	}
	return false;
}
