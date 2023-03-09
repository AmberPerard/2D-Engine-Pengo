#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

namespace dae
{
	class BaseComponent;

	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;
		
		// Scenegraph
		GameObject* GetParent() const { return m_Parent; };
		void SetParent(GameObject* parent, bool keepWorldPosition = false);
		const std::vector<GameObject*>& GetChildren() { return m_Children; };


		//components
		template <typename T> T* AddComponent();
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();

		Transform* GetTransform() const { return m_pTransform; }

	private:
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};

		GameObject* m_Parent{ nullptr };
		std::vector<GameObject*> m_Children{};

		Transform* const m_pTransform;

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	};

	template <typename T>
	T* GameObject::AddComponent()
	{
		static_assert(std::is_base_of<BaseComponent, T>::value, "Provided template argument is not a component");
		auto comp = std::make_unique<T>(this);
		T* dsfa = comp.get();
		m_pComponents.push_back(std::move(comp));
		return dsfa;
	}

	template <typename T>
	T* GameObject::GetComponent() const
	{
		for (auto& comp : m_pComponents)
		{
			T* ptr = dynamic_cast<T*>(comp.get());
			if(ptr)
			{
				return ptr;
			}
		}
		return nullptr;
	}

	template <typename T>
	void GameObject::RemoveComponent()
	{
		for (auto it = begin(m_pComponents); it != end(m_pComponents); ++it)
		{
			if (dynamic_cast<T*>(it->get()))
			{
				m_pComponents.erase(it);
				break;
			}
		}
	}
}
