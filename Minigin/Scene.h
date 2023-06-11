#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;
		void RenderUI();

		void Unload();

		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string GetName() const { return m_name; }

	private: 
		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}
