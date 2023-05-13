#pragma once
#include <iostream>
#include <rapidjson.h>
#include <document.h>
#include <filereadstream.h>
#include <string>

namespace dae
{
	rapidjson::Document ReadJsonFile(const std::string& filePath)
	{
		FILE* fp = nullptr;

		fopen_s(&fp, filePath.c_str(), "r");
		if (fp == nullptr)
		{
						std::cout << "Failed to open file: " << filePath << std::endl;
			return nullptr;
		}

		std::string fileName = filePath;
		rapidjson::Document jsonFile;
		FILE* pFile = nullptr;

		fopen_s(&pFile, fileName.c_str(), "rb");

		if (pFile != nullptr)
		{
			fseek(pFile, 0, SEEK_END);
			const size_t size = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);
			char* readBuffer = new char[size];
			rapidjson::FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
			jsonFile.ParseStream(inputStream);
			delete[] readBuffer;
			fclose(pFile);
		}

		return jsonFile;
	}
}


