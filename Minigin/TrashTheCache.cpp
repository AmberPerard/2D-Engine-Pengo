#include "TrashTheCache.h"

#include <chrono>
#include <map>
#include <numeric>

void TrashTheCache::FirstExercise(int sampleSize)
{
	m_Exercise1XData.clear();
	m_Exercise1YData.clear();

	int length = 1000000;
	std::vector<int> arry(length,0);
	int stepsize;

	// To store sample data
	std::map<int, std::vector<float>> sampleData{};

	for (int index{ 0 }; index < sampleSize; index++)
	{
		for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < length; i += stepsize) arry[i] *= 2;

			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());



			if (sampleData.count(stepsize) == 0)
			{
				sampleData[stepsize] = std::vector<float>{};  // Create vector if the key doesnt exist yet.
			}
			sampleData[stepsize].push_back(elapsedTime);
		}
	}
	for (auto data : sampleData)
	{
		// Calculate average
		auto total{ std::accumulate(begin(data.second), end(data.second), 0.f) };
		double average{ total / static_cast<float>(sampleSize) };

		m_Exercise1XData.push_back(static_cast<float>(data.first));
		m_Exercise1YData.push_back(static_cast<float>(average));
	}

}

void TrashTheCache::SecondExercise(int sampleSize)
{

	m_Exercise2XData.clear();
	m_Exercise2YData.clear();

	const int length = 1000000;
	std::vector<GameObject3D> arry(length);

	int stepsize;

	// To store sample data
	std::map<int, std::vector<float>> sampleData{};
	for (int index{ 0 }; index < sampleSize; index++)
	{
		for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < length; i += stepsize) arry[i].ID *= 2;

			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());


			if (sampleData.count(stepsize) == 0)
			{
				sampleData[stepsize] = std::vector<float>{};  // Create vector if the key doesnt exist yet.
			}
			sampleData[stepsize].push_back(elapsedTime);
		}
	}
	for (auto data : sampleData)
	{
		// Delete biggest and smallest element from the samples
		data.second.erase(std::max_element(begin(data.second), end(data.second)));
		data.second.erase(std::min_element(begin(data.second), end(data.second)));

		// Calculate average
		auto total{ std::accumulate(begin(data.second), end(data.second), 0.f) };
		double average{ total / static_cast<float>(sampleSize) };

		m_Exercise2XData.push_back(static_cast<float>(data.first));
		m_Exercise2YData.push_back(static_cast<float>(average));
	}
}

void TrashTheCache::SecondExerciseALT(int sampleSize)
{
	m_Exercise2AltXData.clear();
	m_Exercise2AltYData.clear();

	const int length = 1000000;
	std::vector<GameObject3DALT> arry(length);

	// To store sample data
	std::map<int, std::vector<float>> sampleData{};
	int stepsize;
	for (int index{ 0 }; index < sampleSize; index++)
	{
		for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < length; i += stepsize) arry[i].ID *= 2;

			auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());


			if (sampleData.count(stepsize) == 0)
			{
				sampleData[stepsize] = std::vector<float>{};  // Create vector if the key doesnt exist yet.
			}
			sampleData[stepsize].push_back(elapsedTime);
		}
	}
	for (auto data : sampleData)
	{
		// Delete biggest and smallest element from the samples
		data.second.erase(std::max_element(begin(data.second), end(data.second)));
		data.second.erase(std::min_element(begin(data.second), end(data.second)));

		// Calculate average
		auto total{ std::accumulate(begin(data.second), end(data.second), 0.f) };
		double average{ total / static_cast<float>(sampleSize) };

		m_Exercise2AltXData.push_back(static_cast<float>(data.first));
		m_Exercise2AltYData.push_back(static_cast<float>(average));
	}
}
