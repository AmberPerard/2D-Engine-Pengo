#include "BaseComponent.h"

#include "GameObject.h"

dae::BaseComponent::BaseComponent(GameObject* pGameObject)
	:m_pGameObject(pGameObject)
{
}
