#pragma once
#include <iostream>
#include <rapidjson.h>
#include <document.h>
#include <filereadstream.h>
#include <fstream>
#include <string>
#include <istreamwrapper.h>

namespace dae
{
	std::vector<int> ReadJsonFile(const std::string& filePath)
	{
		using rapidjson::Document;
		std::ifstream is{ filePath };
		std::vector<int> positions;


		if (!is.is_open()) {
			std::cout << "Failed to open the file." << std::endl;
			return positions;
		}

		// Read the contents of the file into a string
		std::string jsonString((std::istreambuf_iterator(is)), std::istreambuf_iterator<char>());

		// Parse the JSON string
		Document document;
		document.Parse(jsonString.c_str());

		is.close();

		if (document.IsArray()) {
			const rapidjson::Value& array = document[0]["BlockSpawns"];
			if (array.IsArray()) {
				for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
					int pos;
					pos = array[i].GetInt();
					positions.push_back(pos);
				}
			}
		}
		return positions;
	}
}


