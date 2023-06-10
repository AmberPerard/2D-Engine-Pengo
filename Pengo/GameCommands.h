#pragma once
#include "Command.h"

class Move final : public dae::Command
{
public:
	Move(std::shared_ptr<dae::GameObject> pActor, glm::vec2 dir, int Blocksize);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_pActor{};
	glm::vec2 m_Dir{};
	int m_Blocksize{};
};

class Push final : public dae::Command
{
	public:
	Push(std::shared_ptr<dae::GameObject> pActorr);
	void Execute() override;
	private:
	std::shared_ptr<dae::GameObject> m_pActor{};
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

class SwitchLevel final : public dae::Command
{
public:
	SwitchLevel() = default;
	void Execute() override;
};