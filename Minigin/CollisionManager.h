#pragma once
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Singleton.h"

namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void Add(ColliderComponent* colliderComponent);
		void Remove(ColliderComponent* colliderComponent);

		void FixedUpdate();
	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		std::vector<ColliderComponent*> m_CollisionObjects{};
		bool CheckCollision(ColliderComponent* firstCollider, ColliderComponent* secondCollider);
	};
}