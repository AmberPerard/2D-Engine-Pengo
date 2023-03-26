#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "GameObject.h"

namespace dae
{
	
	class Command
	{
	protected:
		std::shared_ptr<GameObject> GetObject() const { return object; }
	public:
		Command(std::shared_ptr<GameObject> object);
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;

	private:
		std::shared_ptr<GameObject> object;
	};

	class Move : public Command
	{
	public:
		Move(std::shared_ptr<GameObject> object);
		void Execute() override;
	private:
		glm::vec2 m_Dir{};
		float m_Speed{};
		float m_Acceleration{}; 
	};

}
#pragma once