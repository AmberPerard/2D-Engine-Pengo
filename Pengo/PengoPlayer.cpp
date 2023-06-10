#include "PengoPlayer.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "RenderComponent.h"

PengoPlayer::PengoPlayer(dae::Scene& scene, glm::vec2 position, float scale, std::string texturePath)
{
	auto player = std::make_shared<dae::GameObject>();
	player->AddComponent<dae::RenderComponent>()->SetTexture(texturePath);
	player->AddComponent<CharacterComponent>();
	player->GetTransform()->SetPosition({ position.x,position.y });
	player->GetTransform()->SetScale(scale);
	scene.Add(player);
}
