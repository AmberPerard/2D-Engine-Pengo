#pragma once
#include <functional>
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class ColliderComponent final : public BaseComponent
	{
		typedef std::function<void(GameObject* otherGameObject)> CollisionCallback;
	public:
		ColliderComponent(GameObject* pGameObject);
		~ColliderComponent() override;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		void SetSize(glm::vec2 size) { m_Size = size; }
		glm::vec3 GetOwnerPosition() const;
		glm::vec2 GetSize() const { return m_Size; }
		void OnCollision(ColliderComponent* other);
		void SetCollisionCallback(CollisionCallback callback) { m_CollisionCallback = callback; }
	private:
		glm::vec2 m_Size;
		CollisionCallback m_CollisionCallback;
	};
}
