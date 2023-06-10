#pragma once
#include <glm/vec2.hpp>

#include "BlockComponent.h"
#include "Singleton.h"

class BlocksManager final : public dae::Singleton<BlocksManager>
{
public:
	BlocksManager() = default;
	~BlocksManager() = default;

	void AddBlock(BlockComponent* collision);
	void RemoveBlock(BlockComponent* collision);

	BlockComponent* FindWall(glm::vec2 pos);

	void AddSpawner(BlockComponent* spawner);
	void RemoveSpawner(BlockComponent* spawner);

	const std::vector<BlockComponent*>& GetSpawners() const;

private:
	std::vector<BlockComponent*> m_Blocks{};
	std::vector<BlockComponent*> m_Spawners{};
};

