#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "EnemyComponent.h"
#include "Singleton.h"

class EnemyManager final : public dae::Singleton<EnemyManager>
{
public:
	void AddEnemy(EnemyComponent* enemy);
	void RemoveEnemy(EnemyComponent* enemy);

	//EnemyComponent* FindEnemy(glm::vec2 pos);

private:
	friend class Singleton<EnemyManager>;
	EnemyManager() = default;
	std::vector<EnemyComponent*> m_Enemies{};
};

