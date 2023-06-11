#pragma once
#include "ButtonComponent.h"

class MenuButtonComponent final : public dae::ButtonComponent
{
public:
	MenuButtonComponent(dae::GameObject* gameObject);
	~MenuButtonComponent() override = default;
	MenuButtonComponent(const MenuButtonComponent& other) = delete;
	MenuButtonComponent(MenuButtonComponent&& other) = delete;
	MenuButtonComponent& operator=(const MenuButtonComponent& other) = delete;
	MenuButtonComponent& operator=(MenuButtonComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void RenderUI() override;

	void OnClick() override;
	void SetSceneToOpen(const std::string& sceneName);
	private:
		std::string m_SceneToOpen;
};

