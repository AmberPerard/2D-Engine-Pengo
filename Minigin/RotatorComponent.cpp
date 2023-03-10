#include "RotatorComponent.h"
#include "GameObject.h"
#include "Time.h"
#include "glm/gtx/rotate_vector.hpp"

dae::RotatorComponent::RotatorComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
	m_pTransform = GetOwner()->GetTransform();
}

void dae::RotatorComponent::Update()
{
	const auto localPos = m_pTransform->GetLocalPosition();
	const glm::vec2 newPosition{ glm::rotate(glm::vec2{localPos.x,localPos.y}, glm::radians(m_AnglePerSec) * Time::GetInstance().GetDeltaTime()) };
	m_pTransform->SetPosition(newPosition.x,newPosition.y);
}
