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

		void SetPosition(glm::vec2 pos);
		void SetWorldPosition(glm::vec2 pos) { m_worldPosition = pos; }

		void SetScale(float scale);
		void SetScale(glm::vec2 pos);

		glm::vec2 GetWorldPosition();
		glm::vec2 GetLocalPosition() { return m_localPosition; }

		glm::vec2 GetWorldScale();
		glm::vec2 GetLocalScale() { return m_localScale; }

		glm::vec2 GetForwardVector() { return m_ForwardVector; }
		void SetForwardVector(glm::vec2 forward) { m_ForwardVector = forward; }

		void SetParent(Transform* gameObject);
		void SetDirty() { m_isDirty = true; }
		void SetDirtyScale() { m_isScaleDirty = true; }

		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void RenderUI() override;
	private:
		void UpdateWorldPos();
		void UpdateWorldScale();

	private:
		glm::vec2 m_localScale{1};
		glm::vec2 m_worldScale{1};
		glm::vec2 m_localPosition{};
		glm::vec2 m_worldPosition{};

		glm::vec2 m_ForwardVector{0,1};

		Transform* m_parent{};

		bool m_isDirty{ false };
		bool m_isScaleDirty{ false };
	};
}
