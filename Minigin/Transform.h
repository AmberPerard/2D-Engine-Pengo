#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"
namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y);
		void SetPosition(float x, float y, float z);

		Transform(GameObject* gameObject);
		~Transform() override = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		void Update() override;
		void Render() override;
	private:
		glm::vec3 m_position{};
	};
}
