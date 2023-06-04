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
			block->GetTransform()->SetPosition(36 + (blockDimensions.x * 2 * column) , 36 + (blockDimensions.y * 2 * row));
			block->GetTransform()->SetScale(2);
			scene.Add(block);
		}
	}
}
