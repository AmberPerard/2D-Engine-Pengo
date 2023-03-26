#include <windows.h>
#include <Xinput.h>
#include <glm/glm.hpp>
#include "XController.h"

using namespace dae;

class XController::XControllerImpl
{

	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame{};
	WORD buttonsReleasedThisFrame{};

	int controllerIndex;
public:
	XControllerImpl(int controllerIndex)
		:controllerIndex(controllerIndex)
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}

	bool IsButtonDownThisFrame(unsigned button) const
	{
		return buttonsPressedThisFrame & button;
	}

	bool IsButtonUpThisFrame(unsigned button) const
	{
		return buttonsReleasedThisFrame & button;
	}

	bool IsPressed(unsigned button) const
	{
		return currentState.Gamepad.wButtons & button;
	}

	bool IsLeftInDeadZone() const
	{
		short sX = currentState.Gamepad.sThumbLX;
		short sY = currentState.Gamepad.sThumbLY;

		if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			return false;
		if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			return false;

		return true;
	};

	bool IsRightInDeadZone() const
	{
		short sX = currentState.Gamepad.sThumbRX;
		short sY = currentState.Gamepad.sThumbRY;

		if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			return false;

		if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			return false;

		return true;
	};


	glm::vec2 GetLeftThumbStick() const
	{
		auto leftXnormalized = currentState.Gamepad.sThumbLX / 255.f;
		auto leftYnormalized = currentState.Gamepad.sThumbLY / 255.f;

		glm::vec2 displacement{ leftXnormalized, -leftYnormalized };

		if (IsLeftInDeadZone())
		{
			return glm::vec2(0);
		}

		return glm::normalize(displacement);
	};

	glm::vec2 GetRightThumbStick() const
	{
		auto rightXnormalized = currentState.Gamepad.sThumbRX / 255.f;
		auto rightYnormalized = currentState.Gamepad.sThumbRY / 255.f;

		glm::vec2 displacement{ rightXnormalized, rightYnormalized };

		if (IsRightInDeadZone())
		{
			return glm::vec2(0);
		}

		return glm::normalize(displacement);
	};
};


void XController::Update()
{
	pImpl->Update();
}

bool XController::IsButtonDownThisFrame(ControllerButton button) const
{
	return pImpl->IsButtonDownThisFrame(static_cast<unsigned int>(button));
}

bool XController::IsButtonUpThisFrame(ControllerButton button) const
{
	return pImpl->IsButtonUpThisFrame(static_cast<unsigned int>(button));
}

bool XController::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

glm::vec2 XController::GetLeftThumbStick() const
{
	return pImpl->GetLeftThumbStick();
}

glm::vec2 XController::GetRightThumbStick() const
{
	return pImpl->GetRightThumbStick();
}

XController::XController(int controllerIndex)
{
	pImpl = new XControllerImpl(controllerIndex);
}

XController::~XController()
{
	delete pImpl;
}
