#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "CharacterComponent.h"
#include "ColliderComponent.h"
#include "GameCommands.h"
#include "GameInfo.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PengoLevelLoader.h"
#include "PengoPlayer.h"
#include "PengoSounds.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreDisplayComponent.h"
#include "SDLSoundSystem.h"
#include "ServiceManager.h"
#include "SoundLoggerSystem.h"
#include "TextComponent.h"

void LoadPengoLevel(dae::Scene& scene, std::string levelFile);
void CreatePlayer1(dae::Scene& scene);
void CreatePlayer2(dae::Scene& scene);

void loadLevel()
{
	dae::InputManager::GetInstance().Clear();
	dae::InputManager::GetInstance().AddController();

	std::shared_ptr<dae::Scene> newScene = std::make_shared<dae::Scene>("Game: Pengo - Amber Perard");
	LoadPengoLevel(*newScene, GameInfo::GetInstance().m_CurrentMap);
	dae::SceneManager::GetInstance().LoadScene(newScene);

	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_F1, dae::State::Release,
		std::make_unique<SwitchLevel>()
	);
}

void load()
{
#if _DEBUG
	dae::ServiceManager::register_sound_system(
		std::make_unique<dae::SoundLoggerSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
	dae::ServiceManager::register_sound_system(std::make_unique<dae::SDLSoundSystem>());
#endif

	auto& ss = dae::ServiceManager::get_sound_system();
	ss.AddSoundMusic(PengoSounds[MAIN_SONG], MAIN_SONG);
	ss.AddSoundEffect(PengoSounds[PUNCH_BLOCK], PUNCH_BLOCK);


	loadLevel();
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

void LoadPengoLevel(dae::Scene& scene, std::string levelFile)
{

	auto background = std::make_shared<dae::GameObject>();
	background->AddComponent<dae::RenderComponent>()->SetTexture("PengoBackGround.png");
	background->GetTransform()->SetPosition({ 20,70 });
	background->GetTransform()->SetScale(2);
	scene.Add(background);

	//Load Level 1
	PengoLevelLoader::LoadLevel(levelFile, scene);

	//controls
	dae::InputManager::GetInstance().AddController();
	CreatePlayer1(scene);
	//CreatePlayer2(scene);

	auto& ss = dae::ServiceManager::get_sound_system();
	ss.Play(MAIN_SONG, 60, dae::SoundType::Music); // play music
	//ss.Play(PUNCH_BLOCK, 60, dae::SoundType::Effect); // play music

}

void CreatePlayer1(dae::Scene& scene)
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
	player1Lives->GetTransform()->SetPosition({ GameInfo::GetInstance().GetPlayFieldOffset().x, 20});
	scene.Add(player1Lives);

	//player 1 display score 
	auto player1Score = std::make_shared<dae::GameObject>();
	player1Score->AddComponent<dae::RenderComponent>();
	text = player1Score->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	text->SetText("Score: 0");
	text->SetColor({ 255,10,10 });
	auto scoreComponentPlayer1 = player1Score->AddComponent<dae::ScoreDisplayComponent>();
	player1Score->GetTransform()->SetPosition({ GameInfo::GetInstance().GetPlayFieldOffset().x + 100, 20});
	scene.Add(player1Score);

	//player 1
	auto player1 = std::make_shared<dae::GameObject>();
	player1->AddComponent<dae::RenderComponent>()->SetTexture("a1.png");
	dae::ColliderComponent* collider = player1->AddComponent<dae::ColliderComponent>();
	player1->AddComponent<CharacterComponent>();
	player1->GetComponent<CharacterComponent>()->AddObserver(displayComponentPlayer1);
	player1->GetComponent<CharacterComponent>()->AddObserver(scoreComponentPlayer1);
	collider->SetSize(glm::vec2{ 26, 26 });
	collider->setOffset(glm::vec2{ 3, 3 });
	//collider->EnableDebug();
	player1->GetTransform()->SetPosition({ GameInfo::GetInstance().GetPlayFieldOffset().x, GameInfo::GetInstance().GetPlayFieldOffset().y + 32 });
	player1->GetTransform()->SetScale(2);
	scene.Add(player1);

	// player 1
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_w, dae::State::Release,
		std::make_unique<Move>(player1, glm::vec2{ 0, -1 }, 32)
	);
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_s, dae::State::Release,
		std::make_unique<Move>(player1, glm::vec2{ 0, 1 }, 32)
	);
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_a, dae::State::Release,
		std::make_unique<Move>(player1, glm::vec2{ -1, 0 }, 32)
	);
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_d, dae::State::Release,
		std::make_unique<Move>(player1, glm::vec2{ 1, 0 }, 32)
	);

	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_r, dae::State::Release,
		std::make_unique<Push>(player1)
	);

	// Tempo buttons to kill and hurt the enemy
	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_f, dae::State::Release,
		std::make_unique<Kill>(player1)
	);

	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_j, dae::State::Release,
		std::make_unique<HitEnemy>(player1)
	);

	dae::InputManager::GetInstance().CreateKeyboardCommand(SDLK_k, dae::State::Release,
		std::make_unique<CrushEnemy>(player1)
	);
}

void CreatePlayer2(dae::Scene& scene)
{
	//player 2
	auto player2 = std::make_shared<dae::GameObject>();
	player2->AddComponent<dae::RenderComponent>()->SetTexture("a2.png");
	player2->AddComponent<CharacterComponent>();
	dae::ColliderComponent* collider2 = player2->AddComponent<dae::ColliderComponent>();
	collider2->SetSize(glm::vec2{ 32, 32 });
	player2->GetTransform()->SetPosition({ 320 + 20, 300 + 10 });
	player2->GetTransform()->SetScale(2);
	scene.Add(player2);

	// player 2
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Up, dae::State::Hold,
		std::make_unique<Move>(player2, glm::vec2{ 0, -1 }, 32)
	);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Down, dae::State::Hold,
		std::make_unique<Move>(player2, glm::vec2{ 0, 1 }, 32)
	);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Left, dae::State::Hold,
		std::make_unique<Move>(player2, glm::vec2{ -1, 0 }, 32)
	);
	dae::InputManager::GetInstance().CreateControllerCommand(dae::XController::ControllerButton::Right, dae::State::Hold,
		std::make_unique<Move>(player2, glm::vec2{ 1, 0 }, 32)
	);
}

