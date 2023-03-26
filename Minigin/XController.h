#pragma once
namespace dae
{
	class XController final
	{
		class XControllerImpl;
		XControllerImpl* pImpl;
	public:
		enum class ControllerButton
		{
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
			Up = 0x0001,
			Down = 0x0002,
			Left = 0x0004,
			Right = 0x0008,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			Start = 0x0010,
			Back = 0x0020
		};

		void Update();

		bool IsButtonDownThisFrame(ControllerButton button) const;
		bool IsButtonUpThisFrame(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		glm::vec2 GetLeftThumbStick() const;
		glm::vec2 GetRightThumbStick() const;

		explicit XController(int controllerIndex);
		~XController();
	};
};