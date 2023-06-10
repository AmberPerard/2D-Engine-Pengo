#include "BlocksManager.h"

#include <iostream>
#include <ostream>

void BlocksManager::AddBlock(BlockComponent* collision)
{
	auto it = std::find(m_Blocks.begin(), m_Blocks.end(), collision);
	if (it == m_Blocks.end())
	{
		m_Blocks.push_back(collision);
	}
}

void BlocksManager::RemoveBlock(BlockComponent* collision)
{
	auto it = std::find(m_Blocks.begin(), m_Blocks.end(), collision);
	if (it != m_Blocks.end())
	{
		m_Blocks.erase(it);
	}
}

BlockComponent* BlocksManager::FindWall(glm::vec2 pos)
{
	for (auto block : m_Blocks)
	{
		if (block->GetPosition() == pos)
		{
			return block;
		}
	}
	return nullptr;
}

void BlocksManager::AddSpawner(BlockComponent* spawner)
{
	if (std::find(m_Spawners.begin(), m_Spawners.end(), spawner) == m_Spawners.end())
	{
		m_Spawners.push_back(spawner);
	}
}

void BlocksManager::RemoveSpawner(BlockComponent* spawner)
{
	auto it = std::find(m_Spawners.begin(), m_Spawners.end(), spawner);
	if (it != m_Spawners.end())
	{
		m_Spawners.erase(it);
	}
}

const std::vector<BlockComponent*>& BlocksManager::GetSpawners() const
{
	return m_Spawners;
}
