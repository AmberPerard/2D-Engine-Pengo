#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject()
{
}

void dae::GameObject::Update()
{

	for (const auto& comp : m_pComponents)
	{
		if(!comp->IsMarkedForDeletion())
		{
			comp->Update();
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::SetParent([[maybe_unused]]GameObject* parent, [[maybe_unused]] bool keepWorldPosition)
{

}
