#pragma once
#include <vector>
#include <XInput.h>

#include "Singleton.h"

namespace dae
{
	enum class Button
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		Up = XINPUT_GAMEPAD_DPAD_UP,
		Down = XINPUT_GAMEPAD_DPAD_DOWN,
		Left = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK
	};

	class InputManager final : public Singleton<InputManager>
	{
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};

		unsigned int m_ButtonsPressedThisFrame{};
		unsigned int m_ButtonsReleasedThisGame{};
	public:
		bool ProcessInput();
		bool IsButtonDownThisFrame(unsigned int button) const;
		bool IsButtonUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;


	};
}
