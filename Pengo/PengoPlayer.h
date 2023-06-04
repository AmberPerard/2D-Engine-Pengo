#pragma once
#include "Scene.h"
#include <glm/glm.hpp>

class PengoPlayer final
{
public:
	PengoPlayer(dae::Scene& scene, glm::vec2 position, float scale, std::string texturePath );
	~PengoPlayer() = default;
};

