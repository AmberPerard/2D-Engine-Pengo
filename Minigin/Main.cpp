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
#include "imgui.h"
#include "RotatorComponent.h"

void LoadWeek1(dae::Scene& scene);
void LoadWeek2(dae::Scene& scene);
void LoadWeek4();


void load()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//LoadWeek1(scene);
	//LoadWeek2(scene);
	LoadWeek4();

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}

void LoadWeek1(dae::Scene& scene)
{
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

	textObject->GetTransform()->SetPosition(80, 20);
	scene.Add(textObject);

	auto imgObject = std::make_shared<dae::GameObject>();
	imgObject->AddComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	imgObject->GetTransform()->SetPosition(216, 180);
	scene.Add(imgObject);

	auto fpsObject = std::make_shared<dae::GameObject>();
	fpsObject->AddComponent<dae::RenderComponent>();
	auto fontFps = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto textcomp = fpsObject->AddComponent<dae::TextComponent>();

	textcomp->SetFont(fontFps);
	textcomp->SetText("FPS");
	textcomp->SetColor({ 255,255,10 });

	fpsObject->AddComponent<dae::FPSComponent>();
	fpsObject->GetTransform()->SetPosition(10, 20);
	scene.Add(fpsObject);
}
void LoadWeek2(dae::Scene& scene)
{
	const auto centerPoint = std::make_shared<dae::GameObject>();
	centerPoint->GetTransform()->SetPosition(320, 300);


	const auto pengo = std::make_shared<dae::GameObject>();
	const auto renderPengo = pengo->AddComponent<dae::RenderComponent>();
	pengo->AddComponent<dae::RotatorComponent>();
	pengo->GetTransform()->SetPosition(30, 30);
	renderPengo->SetTexture("a1.png");
	pengo->SetParent(centerPoint);

	const auto ball = std::make_shared<dae::GameObject>();
	const auto renderBall = ball->AddComponent<dae::RenderComponent>();
	ball->AddComponent<dae::RotatorComponent>()->SetRotationSpeed(150);
	ball->GetTransform()->SetPosition(20, 10);
	renderBall->SetTexture("a2.png");
	ball->SetParent(pengo);

	scene.Add(centerPoint);
}

void LoadWeek4()
{

}
