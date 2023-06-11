#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::LoadScene(std::shared_ptr<Scene> scene)
{
	m_pActiveScene = scene;
}

void dae::SceneManager::Update()
{

	m_pActiveScene->Update();

}

void dae::SceneManager::FixedUpdate()
{

	m_pActiveScene->FixedUpdate();

}

void dae::SceneManager::Render()
{

	m_pActiveScene->Render();

}

void dae::SceneManager::RenderUI()
{

	m_pActiveScene->RenderUI();

}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(std::string name)
{
	for (auto scene : m_pScenes)
	{
		if (scene->GetName() == name)
		{
			return scene;
		}
	}
	return nullptr;
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_pScenes.push_back(scene);
}

