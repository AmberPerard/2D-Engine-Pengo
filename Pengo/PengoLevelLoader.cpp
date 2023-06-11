#include "PengoLevelLoader.h"
#include <vector>
#include "BlockComponent.h"
#include "BlocksManager.h"
#include "BlockStates.h"
#include "ColliderComponent.h"
#include "GameInfo.h"
#include "GameObject.h"
#include "JsonParser.h"
#include "RenderComponent.h"
#include "RigidBody.h"
#include "StateMachine.h"

void PengoLevelLoader::LoadLevel(const std::string& filePath, dae::Scene& scene)
{
	std::vector<int> positions = dae::ReadJsonFile(filePath);
	auto  dimensions = GameInfo::GetInstance().GetBlockSize();
	auto rows = GameInfo::GetInstance().GetNrOfRows();
	auto columns = GameInfo::GetInstance().GetNrOfColumns();
	auto offset = GameInfo::GetInstance().GetPlayFieldOffset();
	const float scale = 2;
	for (int column = 0; column < columns; ++column)
	{
		for (int row = 0; row < rows; ++row)
		{
			if (std::find(positions.begin(), positions.end(), column + columns * row) == positions.end())
			{
				continue;
			}
			auto block = std::make_shared<dae::GameObject>();
			block->AddComponent<dae::RenderComponent>()->SetTexture("PengoBlock.png");
			auto collision = block->AddComponent<dae::ColliderComponent>();
			collision->SetSize(glm::vec2{dimensions.x - 2, dimensions.y - 2});
			collision->setOffset(glm::vec2{1, 1});
			//collision->EnableDebug();
			auto blockComp = block->AddComponent<BlockComponent>();
			blockComp->SetRow(row);
			blockComp->SetColumn(column);
			BlocksManager::GetInstance().AddBlock(blockComp);
			block->AddComponent<dae::RigidBody>()->SetMovementSpeed({ 200,200 });
			block->AddComponent<dae::StateMachine>()->Initialize(std::make_unique<WallIdleState>());
			block->GetTransform()->SetPosition({ offset.x + (dimensions.x * column) , offset.y + (dimensions.y * row) });
			block->GetTransform()->SetScale(scale);
			scene.Add(block);
		}
	}
	buildSideWalls(scene);
}

void PengoLevelLoader::buildSideWalls(dae::Scene& scene)
{
	auto  dimensions = GameInfo::GetInstance().GetBlockSize();
	auto rows = GameInfo::GetInstance().GetNrOfRows();
	auto columns = GameInfo::GetInstance().GetNrOfColumns();
	auto offset = GameInfo::GetInstance().GetPlayFieldOffset();
	//Left
	for (int row{ 0 }; row < rows; row++)
	{
		auto sideblock = std::make_shared<dae::GameObject>();
		auto blockComp = sideblock->AddComponent<BlockComponent>();
		blockComp->SetStatic(true);
		blockComp->SetRow(row);
		blockComp->SetColumn(-1);
		auto collider = sideblock->AddComponent<dae::ColliderComponent>();
		collider->SetSize(glm::vec2{dimensions.x - 2, dimensions.y - 2});
		collider->setOffset(glm::vec2{1, 1});
		//collider->EnableDebug();
		sideblock->GetTransform()->SetPosition({ offset.x - dimensions.x, offset.y + (dimensions.y * row) });
		scene.Add(sideblock);
	}

	//Top
	for (int column{ 0 }; column < columns; column++)
	{
		auto sideblock = std::make_shared<dae::GameObject>();
		auto blockComp = sideblock->AddComponent<BlockComponent>();
		blockComp->SetStatic(true);
		blockComp->SetRow(-1);
		blockComp->SetColumn(column);
		auto collider = sideblock->AddComponent<dae::ColliderComponent>();
		collider->SetSize(glm::vec2{dimensions.x - 2, dimensions.y - 2});
		collider->setOffset(glm::vec2{1, 1});
		//collider->EnableDebug();
		sideblock->GetTransform()->SetPosition({ offset.x + (dimensions.x * column), offset.y - dimensions.y });
		scene.Add(sideblock);
	}

	//Right
	for (int row{ 0 }; row < rows; row++)
	{
		auto sideblock = std::make_shared<dae::GameObject>();
		auto blockComp = sideblock->AddComponent<BlockComponent>();
		blockComp->SetStatic(true);
		blockComp->SetRow(row);
		blockComp->SetColumn(columns );
		auto collider = sideblock->AddComponent<dae::ColliderComponent>();
		collider->SetSize(glm::vec2{dimensions.x - 2, dimensions.y - 2});
		collider->setOffset(glm::vec2{1, 1});
		//collider->EnableDebug();
		sideblock->GetTransform()->SetPosition({ offset.x + (columns * dimensions.x), offset.y + (dimensions.y * row) });
		scene.Add(sideblock);
	}

	//Bottom
	for (int column{ 0 }; column < columns; column++)
	{
		auto sideblock = std::make_shared<dae::GameObject>();
		auto blockComp = sideblock->AddComponent<BlockComponent>();
		blockComp->SetStatic(true);
		blockComp->SetRow(rows);
		blockComp->SetColumn(column);
		auto collider = sideblock->AddComponent<dae::ColliderComponent>();
		collider->SetSize(glm::vec2{dimensions.x - 2, dimensions.y - 2});
		collider->setOffset(glm::vec2{1, 1});
		//collider->EnableDebug();
		sideblock->GetTransform()->SetPosition({ offset.x + (column * dimensions.x), offset.y + (dimensions.y * rows) });
		scene.Add(sideblock);
	}
}
