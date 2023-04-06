#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "GameObject.h"

namespace dae
{
	
	class Command
	{
	public:
		Command();
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;
	};

	class Move : public Command
	{
	public:
		Move(std::shared_ptr<GameObject> pActor, float speed, glm::vec2 dir, float acceleration = 1.f);
		void Execute() override;
	private:
		std::shared_ptr<GameObject> m_pActor{};
		glm::vec2 m_Dir{};
		float m_Speed{};
		float m_Acceleration{}; 
	};

}
#pragma once