#include "MenuButtonComponent.h"

#include "SceneManager.h"

MenuButtonComponent::MenuButtonComponent(dae::GameObject* gameObject)
	:ButtonComponent(gameObject)
{
}

void MenuButtonComponent::Update()
{
	ButtonComponent::Update();
}

void MenuButtonComponent::FixedUpdate()
{
	ButtonComponent::FixedUpdate();
}

void MenuButtonComponent::Render()
{
	ButtonComponent::Render();
}

void MenuButtonComponent::RenderUI()
{
	ButtonComponent::RenderUI();
}

void loadLevel();

void MenuButtonComponent::OnClick()
{
	loadLevel();
}

void MenuButtonComponent::SetSceneToOpen(const std::string& sceneName)
{
	m_SceneToOpen = sceneName;
}
