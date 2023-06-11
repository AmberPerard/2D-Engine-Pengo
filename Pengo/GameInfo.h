#pragma once
#include <string>
#include <glm/vec2.hpp>

#include "Helpers.h"
#include "Singleton.h"

class GameInfo final : public dae::Singleton<GameInfo>
{
public:
	enum Level
	{
		level1,
		level2,
		level3
	};
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

	glm::vec2 GetPlayFieldOffset() const { return m_PlayFieldOffset; }

	MovementDirection FindMovement(glm::vec2 input);

	Level GetCurrentLevel() const { return currentLevel; }
	Level GetNextLevel() const { return LevelToSwapTo; }
	void SetCurrentLevel(Level level) { currentLevel = level; }
	void SetNextLevel(int levelID) { LevelToSwapTo = Level(levelID); }
	int GetMaxScenes() const { return maxScenes; }

	std::string m_CurrentMap{ "../Data/Level1.json" };
	std::vector<std::string> maps{
		"../Data/Level1.json", "../Data/Level2.json", "../Data/Level3.json" };
private:
	int NrOfRows{15};
	int NrOfColums{ 13 };

	int maxScenes{ 3 };
	Level currentLevel{ Level::level2 };
	Level LevelToSwapTo{ Level::level1 };


	glm::vec2 m_PlayFieldOffset{ 37, 36 };
	glm::vec2 m_CollisionSize{26, 26 };
	glm::vec2 m_CollisionOffset{ 3, 3 };
	glm::vec2 m_BlockSize{ 32, 32 };

};
