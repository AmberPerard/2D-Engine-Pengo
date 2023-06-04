#pragma once
#include <string>

#include "Scene.h"

class PengoLevelLoader
{
public:
	static void LoadLevel(const std::string& filePath, dae::Scene& scene);
};

