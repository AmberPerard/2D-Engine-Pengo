#include "PengoLevelLoader.h"
#include "JsonParser.h"
#include <rapidjson.h>

void PengoLevelLoader::LoadLevel(const std::string& filePath, dae::SceneManager& /*scene*/)
{
	rapidjson::Document file = dae::ReadJsonFile(filePath);

	const rapidjson::Value& positionBlocks = file["BlockSpawns"];

	/*auto places = positionBlocks.IsArray();*/
	std::vector<int> positions;


	for (rapidjson::SizeType i = 0; i < positionBlocks.Size(); i++)
	{
		positions.push_back(positionBlocks[i].GetInt());
	}
}
