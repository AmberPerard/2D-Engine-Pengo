#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "Minigin.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "Transform.h"
#include "GameObject.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	const auto backgroundObject = std::make_shared<dae::GameObject>();
	auto renderComp = backgroundObject->AddComponent<dae::RenderComponent>();
	renderComp->SetTexture("background.tga");
	scene.Add(backgroundObject);

	auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	textObject->AddComponent<dae::RenderComponent>();

	auto textComp = textObject->AddComponent<dae::TextComponent>();
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");
	textComp->SetColor({ 255,255,255 });

	const auto trans = textObject->AddComponent<dae::Transform>();
	trans->SetPosition(80, 20);
	scene.Add(textObject);

	auto imgObject = std::make_shared<dae::GameObject>();
	imgObject->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	const auto transImg = imgObject->AddComponent<dae::Transform>();
	transImg->SetPosition(216, 180);
	scene.Add(imgObject);

	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddComponent<dae::RenderComponent>();
	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto textcomp = fpsObject->AddComponent<dae::TextComponent>();

	textcomp->SetFont(fontFps);
	textcomp->SetText("FPS");
	textcomp->SetColor({ 255,255,10 });

	fpsObject->AddComponent<dae::FPSComponent>();
	const auto transFPS = fpsObject->AddComponent<dae::Transform>();
	transFPS->SetPosition(10, 20);
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}