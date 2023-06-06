#include <string>
#include "GameObject.h"

#include <iostream>

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

void dae::GameObject::FixedUpdate()
{
	for (const auto& child : m_pChildren)
	{
		child->FixedUpdate();
	}


	for (const auto& comp : m_pComponents)
	{
		if (!comp->IsMarkedForDeletion())
		{
			comp->FixedUpdate();
		}
		else
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

void dae::GameObject::RenderUI() const
{
	for (const auto& child : m_pChildren)
	{
		child->RenderUI();
	}

	for (const auto& comp : m_pComponents)
	{
		comp->RenderUI();
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
		m_Parent->RemoveChildFromCollection(this->shared_from_this());
	}

	m_Parent = parent.get();

	if (m_Parent)
	{
		m_Parent->AddChildToCollection(this->shared_from_this());
	}
}

void dae::GameObject::AddChildToCollection(std::shared_ptr<dae::GameObject> child)
{
	m_pChildren.emplace_back((child));
}

void dae::GameObject::RemoveChildFromCollection(std::shared_ptr<dae::GameObject> child)
{
	std::erase(m_pChildren, child);
}

