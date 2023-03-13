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

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition)
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

void dae::GameObject::AddChildToCollection(GameObject* child)
{
	m_pChildren.emplace_back(std::move(child));
}

void dae::GameObject::RemoveChildFromCollection(GameObject* child)
{
	std::erase(m_pChildren, child);
}

