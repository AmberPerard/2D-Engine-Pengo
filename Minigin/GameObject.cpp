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
	//check if already has parent
	//if than you how to do position

	// Remove from previous parent if exist
	if (m_Parent)
	{
		m_Parent->RemoveChild(this);
	}

	// Update the parent
	m_Parent = parent;

	// Add to the new parent if it exists
	if (m_Parent)
	{
		m_Parent->AddChild(this);
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase(m_Children, child);
}
