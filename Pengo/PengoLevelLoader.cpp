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
}
