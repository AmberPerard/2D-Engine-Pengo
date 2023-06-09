#include "PengoLevelLoader.h"
#include <vector>

#include "BlockComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "JsonParser.h"
#include "RenderComponent.h"

void PengoLevelLoader::LoadLevel(const std::string& filePath, dae::Scene& scene)
{
	std::vector<int> positions = dae::ReadJsonFile(filePath);
	glm::vec2 blockDimensions{ 16,16 };
	const float scale = 2;
	blockDimensions *= scale;
	for (int column = 0; column < 13; ++column)
	{
		for (int row = 0; row < 15; ++row)
		{
			if(std::find(positions.begin(),positions.end(), column + 13*row) == positions.end())
			{
				continue;
			}
			auto block = std::make_shared<dae::GameObject>();
			block->AddComponent<dae::RenderComponent>()->SetTexture("PengoBlock.png");
			auto collision = block->AddComponent<dae::ColliderComponent>();
			collision->SetSize(glm::vec2{blockDimensions.x - 2, blockDimensions.y - 2});
			collision->setOffset(glm::vec2{1,1});
			block->AddComponent<BlockComponent>();
			block->GetTransform()->SetPosition(36.f + (blockDimensions.x  * column) , 36.f + (blockDimensions.y * row));
			block->GetTransform()->SetScale(scale);
			scene.Add(block);
		}
	}
	auto sideblockLeft = std::make_shared<dae::GameObject>();
	sideblockLeft->AddComponent<BlockComponent>()->SetStatic(true);
	auto collider = sideblockLeft->AddComponent<dae::ColliderComponent>();
	collider->SetSize(glm::vec2{32, 480});
	collider->EnableDebug();
	sideblockLeft->GetTransform()->SetPosition(0, 36);
	scene.Add(sideblockLeft);

	auto sideblockRight = std::make_shared<dae::GameObject>();
	sideblockRight->AddComponent<BlockComponent>()->SetStatic(true);
	auto colliderRight = sideblockRight->AddComponent<dae::ColliderComponent>();
	colliderRight->SetSize(glm::vec2{32, 480});
	colliderRight->EnableDebug();
	sideblockRight->GetTransform()->SetPosition(452, 36);
	scene.Add(sideblockRight);

	auto sideblockTop = std::make_shared<dae::GameObject>();
	sideblockTop->AddComponent<BlockComponent>()->SetStatic(true);
	auto colliderTop = sideblockTop->AddComponent<dae::ColliderComponent>();
	colliderTop->SetSize(glm::vec2{480, 32});
	colliderTop->EnableDebug();
	sideblockTop->GetTransform()->SetPosition(36, 0);
	scene.Add(sideblockTop);

	auto sideblockBot = std::make_shared<dae::GameObject>();
	sideblockBot->AddComponent<BlockComponent>()->SetStatic(true);
	auto colliderBot = sideblockBot->AddComponent<dae::ColliderComponent>();
	colliderBot->SetSize(glm::vec2{480, 32});
	colliderBot->EnableDebug();
	sideblockBot->GetTransform()->SetPosition(36, 512);
	scene.Add(sideblockBot);

}
