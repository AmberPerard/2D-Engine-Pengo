#pragma once
#include <string>
#include "SceneManager.h"

class PengoLevelLoader
{
	static void LoadLevel(const std::string& filePath, dae::SceneManager& scene);
};

