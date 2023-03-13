#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

namespace dae
{
	class BaseComponent;

	class GameObject final: public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;
		
		// Scenegraph
		std::shared_ptr<GameObject> GetParent() const { return m_Parent; }
		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition = false);
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() { return m_pChildren; }

		//components
		template <typename T> T* AddComponent();
		template <typename T> T* GetComponent() const;
		template <typename T> void RemoveComponent();
		template <typename T> void RemoveComponent(T* comp);

		Transform* GetTransform() const { return m_pTransform; }

	private:
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};

		std::shared_ptr<GameObject> m_Parent{ nullptr };
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};

		Transform* m_pTransform{};

		void AddChildToCollection(std::shared_ptr<dae::GameObject> child);
		void RemoveChildFromCollection(std::shared_ptr<dae::GameObject> child);
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

	template <typename T>
	void GameObject::RemoveComponent(T* comp)
	{
		for(auto it = begin(m_pComponents); it != end(m_pComponents); ++it)
		{
			if(dynamic_cast<T*>(it->get()) == comp)
			{
				m_pComponents.erase(it);
				break;
			}
		}
	}
}
