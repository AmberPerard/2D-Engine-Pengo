#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::GameObject()
	:m_pTransform{ new Transform(this) }
{
}

dae::GameObject::~GameObject()
{
	// Delete children
	for (GameObject* child : m_pChildren)
	{
		delete child;
	}
	m_pChildren.clear();

	delete m_pTransform;
}

void dae::GameObject::Update()
{
	for (const auto& child : m_pChildren)
	{
		child->Update();
	}


	for (const auto& comp : m_pComponents)
	{
		if(!comp->IsMarkedForDeletion())
		{
			comp->Update();
		}else
		{
			RemoveComponent(&comp);
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& child : m_pChildren)
	{
		child->Render();
	}

	for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if(parent)
	{
		if(keepWorldPosition)
		{
			m_pTransform->SetPosition(m_pTransform->GetLocalPosition() - parent->GetTransform()->GetWorldPosition());
		}
		m_pTransform->SetDirty();
		m_pTransform->SetParent(parent->GetTransform());
	}
	else
	{
		m_pTransform->SetPosition(m_pTransform->GetWorldPosition());
	}

	if (m_Parent)
	{
		m_Parent->RemoveChildFromCollection(this);
	}

	m_Parent = parent;

	if (m_Parent)
	{
		m_Parent->AddChildToCollection(this);
	}
}

void dae::GameObject::AddChild(GameObject* child, bool keepWorldPosition)
{
	child->SetParent(this, keepWorldPosition);

}

void dae::GameObject::AddChildToCollection(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

void dae::GameObject::RemoveChildFromCollection(GameObject* child)
{
	std::erase(m_pChildren, child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	const auto findItr = std::find(begin(m_pChildren), end(m_pChildren), child);
	if(findItr != end(m_pChildren))
	{
		m_pChildren.erase(findItr);
	}
}
