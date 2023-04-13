#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <ostream>

#include "CharacterComponent.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "InputManager.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "TTCComponent.h"
#include <steam_api.h>

void LoadWeek1(dae::Scene& scene);
void LoadWeek2(dae::Scene& scene);
void LoadWeek4(dae::Scene& scene);
void LoadWeek5(dae::Scene& scene);

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	LoadWeek1(scene);
	LoadWeek5(scene);

}

int main(int, char*[]) {

	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;

	dae::Minigin engine("../Data/");
	engine.Run(load);
	//dae::Minigin engine;
	//engine.Run(LoadGame);

	SteamAPI_Shutdown();
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
	pengo->GetTransform()->SetPosition(30, 30);
	renderPengo->SetTexture("a1.png");
	pengo->SetParent(centerPoint);

	const auto ball = std::make_shared<dae::GameObject>();
	const auto renderBall = ball->AddComponent<dae::RenderComponent>();
	ball->GetTransform()->SetPosition(20, 10);
	renderBall->SetTexture("a2.png");
	ball->SetParent(pengo);

	scene.Add(centerPoint);
}
void LoadWeek4(dae::Scene& scene)
{
	const auto mainObject = std::make_shared<dae::GameObject>();
	mainObject->AddComponent<dae::TTCComponent>();

	scene.Add(mainObject);
}

void LoadWeek5(dae::Scene& scene)
{

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//player 1 display Lives 
	auto player1Lives = std::make_shared<dae::GameObject>();
	player1Lives->AddComponent<dae::RenderComponent>();
	auto text = player1Lives->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	text->SetText("Lives 3");
	text->SetColor({ 255,10,10 });
	auto displayComponentPlayer1 = player1Lives->AddComponent<dae::LivesDisplayComponent>();
	player1Lives->GetTransform()->SetPosition(10, 300);
	scene.Add(player1Lives);

	//player 1 display score 
	auto player1Score = std::make_shared<dae::GameObject>();
	player1Score->AddComponent<dae::RenderComponent>();
	text = player1Score->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	text->SetText("Score: 0");
	text->SetColor({ 255,10,10 });
	auto scoreComponentPlayer1 = player1Score->AddComponent<dae::ScoreDisplayComponent>();
	player1Score->GetTransform()->SetPosition(10, 340);
	scene.Add(player1Score);

	//player 2 display
	auto player2Lives = std::make_shared<dae::GameObject>();
	player2Lives->AddComponent<dae::RenderComponent>();
	text = player2Lives->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	text->SetText("Lives 3");
	text->SetColor({ 10,255,10 });
	auto displayComponentPlayer2 = player2Lives->AddComponent<dae::LivesDisplayComponent>();
	player2Lives->GetTransform()->SetPosition(10, 400);
	scene.Add(player2Lives);

	//player 2 display score 
	auto player2Score = std::make_shared<dae::GameObject>();
	player2Score->AddComponent<dae::RenderComponent>();
	text = player2Score->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	text->SetText("Score: 0");
	text->SetColor({ 10,255,10 });
	auto scoreComponentPlayer2 = player2Score->AddComponent<dae::ScoreDisplayComponent>();
	player2Score->GetTransform()->SetPosition(10, 440);
	scene.Add(player2Score);

	//player 1
	auto player1 = std::make_shared<dae::GameObject>();
	player1->AddComponent<dae::RenderComponent>()->SetTexture("a1.png");
	player1->AddComponent<dae::CharacterComponent>();
	player1->GetComponent<dae::CharacterComponent>()->AddObserver(displayComponentPlayer1);
	player1->GetComponent<dae::CharacterComponent>()->AddObserver(scoreComponentPlayer1);
	player1->GetTransform()->SetPosition(50, 150);
	scene.Add(player1);


	//player 2
	auto player2 = std::make_shared<dae::GameObject>();
	player2->AddComponent<dae::RenderComponent>()->SetTexture("a2.png");
	player2->AddComponent<dae::CharacterComponent>();
	player2->GetComponent<dae::CharacterComponent>()->AddObserver(displayComponentPlayer2);
	player2->GetComponent<dae::CharacterComponent>()->AddObserver(scoreComponentPlayer2);
	player2->GetTransform()->SetPosition(320 + 20, 300 + 10);
	scene.Add(player2);


	//controls
    dae::InputManager::GetInstance().AddController();

	// player 1
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_w, dae::State::Hold,
		std::make_unique<dae::Move>(player1, 200.f, glm::vec2{ 0,-1 })
	);
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_s, dae::State::Hold,
		std::make_unique<dae::Move>(player1, 200.f, glm::vec2{ 0,1 })
	);
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_a, dae::State::Hold,
		std::make_unique<dae::Move>(player1,200.f, glm::vec2{ -1,0 })
	);
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_d, dae::State::Hold,
		std::make_unique<dae::Move>(player1, 200.f, glm::vec2{ 1,0 })
	);


	// Tempo buttons to kill and hurt the enemy
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_f, dae::State::Release,
		std::make_unique<dae::Kill>(player1)
	);

	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_j, dae::State::Release,
		std::make_unique<dae::HitEnemy>(player1)
	);

	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_k, dae::State::Release,
		std::make_unique<dae::CrushEnemy>(player1)
	);

	// player 2
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Up, dae::State::Hold,
		std::make_unique<dae::Move>(player2, 100.f, glm::vec2{ 0,-1 })
		);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Down, dae::State::Hold,
		std::make_unique<dae::Move>(player2, 100.f, glm::vec2{ 0,1 })
	);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Left, dae::State::Hold,
		std::make_unique<dae::Move>(player2, 100.f, glm::vec2{ -1,0 })
	);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Right, dae::State::Hold,
		std::make_unique<dae::Move>(player2, 100.f, glm::vec2{ 1,0 })
	);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::ButtonB, dae::State::Release,
		std::make_unique<dae::Kill>(player2)
	);

	// Tempo buttons to kill and hurt the enemy
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::ButtonA, dae::State::Release,
		std::make_unique<dae::Kill>(player2)
	);

	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::ButtonX, dae::State::Release,
		std::make_unique<dae::HitEnemy>(player2)
	);

	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::ButtonY, dae::State::Release,
		std::make_unique<dae::CrushEnemy>(player2)
	);
}
