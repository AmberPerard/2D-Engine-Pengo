#pragma once
#include <unordered_map>
#include <glm/vec2.hpp>

enum EventType {
	LEVEL_STARTED,
	PLAYER_SPAWNED,
	PLAYER_HIT,
	PLAYER_DIED,
	PLAYER_GAINED_SCORE,
	PLAYER_LOST,
	ENEMY_CRUSHED,
	ENEMY_HIT,
	ENEMY_DIED,

};

enum MovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

inline std::unordered_map DirectionMap
{
	std::make_pair(UP, glm::vec2(0, -1)),
		std::make_pair(DOWN, glm::vec2(0, 1)),
		std::make_pair(LEFT, glm::vec2(-1, 0)),
		std::make_pair(RIGHT, glm::vec2(1, 0)),
		std::make_pair(NONE, glm::vec2(0, 0))
};