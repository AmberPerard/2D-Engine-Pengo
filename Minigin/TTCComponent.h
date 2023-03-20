#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"

namespace dae
{
	class TTCComponent final : public dae::BaseComponent
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
			std::unique_ptr<Transform> transform{};
			int ID{};
		};

		TTCComponent(GameObject* gameObject);
		~TTCComponent() override = default;
		TTCComponent(const TTCComponent& other) = delete;
		TTCComponent(TTCComponent&& other) = delete;
		TTCComponent& operator=(const TTCComponent& other) = delete;
		TTCComponent& operator=(TTCComponent&& other) = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;


	private:
		void FirstExercise(int sampleSize);
		void SecondExercise(int sampleSize);
		void SecondExerciseALT(int sampleSize);

		std::vector<float> m_Exercise1XData{};
		std::vector<float> m_Exercise1YData{};

		std::vector<float> m_Exercise2XData{};
		std::vector<float> m_Exercise2YData{};

		std::vector<float> m_Exercise2AltXData{};
		std::vector<float> m_Exercise2AltYData{};
	};
}
