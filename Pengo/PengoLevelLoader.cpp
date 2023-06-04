#include "PengoLevelLoader.h"
#include <vector>

#include "GameObject.h"
#include "JsonParser.h"
#include "RenderComponent.h"

void PengoLevelLoader::LoadLevel(const std::string& filePath, dae::Scene& scene)
{
	std::vector<int> positions = dae::ReadJsonFile(filePath);
	glm::vec2 blockDimensions{ 16,16 };
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

			block->GetTransform()->SetPosition(36.f + (blockDimensions.x * 2.f * column) , 36.f + (blockDimensions.y * 2.f * row));
			block->GetTransform()->SetScale(2.f);
			scene.Add(block);
		}
	}
}
