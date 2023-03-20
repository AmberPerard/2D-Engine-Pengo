#include "TTCComponent.h"

#include <chrono>
#include <imgui.h>
#include <imgui_plot.h>
#include <map>
#include <numeric>

dae::TTCComponent::TTCComponent(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::TTCComponent::Update()
{
}

void dae::TTCComponent::Render()
{
}

void dae::TTCComponent::RenderUI()
{
	//erxercise 1 
	bool my_tool_active{};
	static bool clickedButton{};
	static bool isCalculated{};
	ImGui::Begin("Exercise1", &my_tool_active, ImGuiWindowFlags_AlwaysAutoResize);

	static int i0 = 10;
	ImGui::InputInt("# Samples", &i0);

	ImGui::PlotConfig conf;
	conf.scale.min = 0;
	conf.tooltip.show = true;
	conf.tooltip.format = "Stepsize:%.0f\nValue: %.0f";
	conf.grid_x.show = false;
	conf.grid_y.show = false;
	conf.frame_size = ImVec2(250, 100);
	conf.line_thickness = 2.0f;

	if (ImGui::Button("Trash the Cache"))
	{
		clickedButton = true;
	}

	if (clickedButton)
	{
		ImGui::Text("Wait for it...");
		FirstExercise(i0);
		isCalculated = true;
		clickedButton = false;
	}
	if (isCalculated)
	{
		conf.values.color = ImColor(255, 150, 0);
		conf.values.xs = m_Exercise1XData.data();
		conf.values.ys = m_Exercise1YData.data();
		conf.values.count = static_cast<int>(m_Exercise1XData.size());
		conf.scale.max = 1024;
		ImGui::Plot("Exercise01", conf);
	}
	ImGui::End();

	//exercise 2
	static bool clickedButtonNormal{};
	static bool isCalculatingNormal{};
	static bool clickedButtonAlt{};
	static bool isCalculatingAlt{};


	ImGui::Begin("Exercise2", &my_tool_active, ImGuiWindowFlags_AlwaysAutoResize);

	static int l0 = 100;
	ImGui::InputInt("# Samples", &l0);
	if (ImGui::Button("Trash the Cache with GameObject3D"))
	{
		clickedButtonNormal = true;
	}
	if (clickedButtonNormal)
	{
		ImGui::Text("Wait for it...");
		SecondExercise(l0);
		isCalculatingNormal = true;
		clickedButtonNormal = false;
	}
	if (isCalculatingNormal)
	{
		conf.values.color = ImColor(255, 150, 0);
		conf.values.xs = m_Exercise2XData.data();
		conf.values.ys = m_Exercise2YData.data();
		conf.values.count = static_cast<int>(m_Exercise2XData.size());
		conf.scale.max = 1024;
		ImGui::Plot("Exercise02 Normal", conf);
	}
	if (ImGui::Button("Trash the Cache with GameObject3DAlt"))
	{
		clickedButtonAlt = true;
		SecondExerciseALT(l0);
		isCalculatingAlt = true;
		clickedButtonAlt = false;
	}
	if (clickedButtonAlt)
	{
		ImGui::Text("Wait for it...");
	}
	if (isCalculatingAlt)
	{
		conf.values.color = ImColor(255, 150, 0);
		conf.values.xs = m_Exercise2AltXData.data();
		conf.values.ys = m_Exercise2AltYData.data();
		conf.values.count = static_cast<int>(m_Exercise2AltXData.size());
		conf.scale.max = 1024;
		ImGui::Plot("Exercise02 Alt", conf);
	}


	if (isCalculatingAlt && isCalculatingNormal)
	{
		static const float* y_data[] = { m_Exercise2YData.data(), m_Exercise2AltYData.data() };
		static ImU32 colors[2] = { ImColor(50, 255, 50), ImColor(50, 50, 255) };

		ImGui::Text("Combined:");
		conf.values.xs = m_Exercise2AltXData.data();
		conf.values.count = static_cast<int>(m_Exercise2AltXData.size());
		conf.values.ys = nullptr; // Clear data
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.colors = colors;

		conf.scale.max = 1024;
		ImGui::Plot("Extra", conf);
	}

	ImGui::End();
}

void dae::TTCComponent::FirstExercise(int sampleSize)
{
	m_Exercise1XData.clear();
	m_Exercise1YData.clear();

	int length = 1000000;
	std::vector<int> arry(length, 0);
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
		// Delete biggest and smallest element from the samples
		data.second.erase(std::max_element(begin(data.second), end(data.second)));
		data.second.erase(std::min_element(begin(data.second), end(data.second)));

		// Calculate average
		auto total{ std::accumulate(begin(data.second), end(data.second), 0.f) };
		double average{ total / static_cast<float>(sampleSize) };

		m_Exercise1XData.push_back(static_cast<float>(data.first));
		m_Exercise1YData.push_back(static_cast<float>(average));
	}
}

void dae::TTCComponent::SecondExercise(int sampleSize)
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

void dae::TTCComponent::SecondExerciseALT(int sampleSize)
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
