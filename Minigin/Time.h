#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	float GetDeltaTime() const { return m_deltaTime; }
	void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }
private:
	float m_deltaTime{};
};

