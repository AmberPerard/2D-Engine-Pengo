#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(GameObject* gameObject);
		~Transform() override = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		void SetPosition(float x, float y);
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 pos);

		void SetScale(float scale);
		void SetScale(float x, float y);
		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 pos);

		glm::vec3 GetWorldPosition();
		glm::vec3 GetLocalPosition() { return m_localPosition; }

		glm::vec3 GetWorldScale();
		glm::vec3 GetLocalScale() { return m_localScale; }

		void SetParent(Transform* gameObject);
		void SetDirty() { m_isDirty = true; }
		void SetDirtyScale() { m_isScaleDirty = true; }

		void Update() override;
		void Render() override;
		void RenderUI() override;
	private:
		void UpdateWorldPos();
		void UpdateWorldScale();

		glm::vec3 m_localScale{1};
		glm::vec3 m_worldScale{1};
		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};

		Transform* m_parent;

		bool m_isDirty{ false };
		bool m_isScaleDirty{ false };
	};
}
