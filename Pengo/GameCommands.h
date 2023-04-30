#pragma once
#include "Command.h"

class Move final : public dae::Command
{
public:
	Move(std::shared_ptr<dae::GameObject> pActor, float speed, glm::vec2 dir, float acceleration = 1.f);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_pActor{};
	glm::vec2 m_Dir{};
	float m_Speed{};
	float m_Acceleration{};
};

class Kill final : public dae::Command
{
public:
	Kill(std::shared_ptr<dae::GameObject> pActor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_pActor{};
};

class HitEnemy final : public dae::Command
{
public:
	HitEnemy(std::shared_ptr<dae::GameObject> pActor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_pActor{};
};

class CrushEnemy final : public dae::Command
{
public:
	CrushEnemy(std::shared_ptr<dae::GameObject> pActor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_pActor{};
};