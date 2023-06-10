#pragma once
#include <glm/vec2.hpp>

#include "Helpers.h"
#include "Singleton.h"

class GameInfo final : public dae::Singleton<GameInfo>
{
public:
	GameInfo() = default;
	~GameInfo() = default;
	GameInfo(const GameInfo& other) = delete;
	GameInfo(GameInfo&& other) = delete;
	GameInfo& operator=(const GameInfo& other) = delete;
	GameInfo& operator=(GameInfo&& other) = delete;

	int GetNrOfRows() const { return NrOfRows; }
	int GetNrOfColumns() const { return NrOfColums; }

	glm::vec2 GetCollisionSize() const { return m_CollisionSize; }
	glm::vec2 GetBlockSize() const { return m_BlockSize; }
	glm::vec2 GetCollisionOffset() const { return m_CollisionOffset; }

	MovementDirection FindMovement(glm::vec2 input);

private:
	int NrOfRows{15};
	int NrOfColums{13};

	glm::vec2 m_CollisionSize{26,26 };
	glm::vec2 m_CollisionOffset{ 3,3 };
	glm::vec2 m_BlockSize{ 32,32 };



};
