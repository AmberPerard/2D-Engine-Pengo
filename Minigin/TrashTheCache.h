#pragma once
#include <vector>

class TrashTheCache
{
public:
	struct Transform
	{
		float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID{};
	};

	class GameObject3DALT
	{
	public:
		Transform* transform;
		int ID;
	};

	void FirstExercise(int sampleSize);
	void SecondExercise(int sampleSize);
	void SecondExerciseALT(int sampleSize);

	std::vector<float>* GetExercise1XData() { return &m_Exercise1XData; }
	std::vector<float>* GetExercise1YData() { return &m_Exercise1YData; }

	std::vector<float>* GetExercise2XData() { return &m_Exercise2XData; }
	std::vector<float>* GetExercise2YData() { return &m_Exercise2YData; }

	std::vector<float>* GetExercise2AltXData() { return &m_Exercise2AltXData; }
	std::vector<float>* GetExercise2AltYData() { return &m_Exercise2AltYData; }

private:
	std::vector<float> m_Exercise1XData{};
	std::vector<float> m_Exercise1YData{};

	std::vector<float> m_Exercise2XData{};
	std::vector<float> m_Exercise2YData{};

	std::vector<float> m_Exercise2AltXData{};
	std::vector<float> m_Exercise2AltYData{};
};

