#pragma once
#include <SDL.h>
#include <vector>

class Keyboard final
{
public:
	explicit Keyboard();
	~Keyboard() = default;

	void Update();

	bool IsButtonPressedThisFrame(SDL_Scancode key) const;
	bool IsButtonReleasedThisFrame(SDL_Scancode key) const;
	bool IsPressed(SDL_Scancode key) const;

private:
	std::vector<Uint8> m_CurrentState{};
	std::vector<Uint8> m_PreviousState{};

	std::vector<Uint8> m_ButtonsPressedThisFrame{};
	std::vector<Uint8> m_ButtonsReleasedThisFrame{};

};

