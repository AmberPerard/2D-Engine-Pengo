#pragma once
#include "Singleton.h"

class GameTime final : public dae::Singleton<GameTime>
{
public:
	float GetDeltaTime() const { return m_deltaTime; }
	void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }
private:
	float m_deltaTime{};
};

