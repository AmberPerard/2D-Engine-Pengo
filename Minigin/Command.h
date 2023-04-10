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

	class Move final : public Command
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

	class Kill final : public Command
	{
	public:
		Kill(std::shared_ptr<GameObject> pActor);
		void Execute() override;
	private:
		std::shared_ptr<GameObject> m_pActor{};
	};

	class HitEnemy final : public Command
	{
	public:
		HitEnemy(std::shared_ptr<GameObject> pActor);
		void Execute() override;
	private:
		std::shared_ptr<GameObject> m_pActor{};
	};

	class CrushEnemy final : public Command
	{
	public:
		CrushEnemy(std::shared_ptr<GameObject> pActor);
		void Execute() override;
	private:
		std::shared_ptr<GameObject> m_pActor{};
	};

}
#pragma once