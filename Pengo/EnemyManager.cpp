#include "EnemyManager.h"

void EnemyManager::AddEnemy(EnemyComponent* enemy)
{
	auto it = std::find(m_Enemies.begin(), m_Enemies.end(), enemy);
	if (it == m_Enemies.end())
	{
		m_Enemies.push_back(enemy);
	}
}

void EnemyManager::RemoveEnemy(EnemyComponent* enemy)
{
	auto it = std::find(m_Enemies.begin(), m_Enemies.end(), enemy);

	if (it != m_Enemies.end())
	{
		m_Enemies.erase(it);
	}
}

