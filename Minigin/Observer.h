#pragma once
namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(int event, GameObject* actor) = 0;
	};
}
