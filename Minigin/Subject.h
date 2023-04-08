#pragma once
#include <memory>
#include <vector>

namespace dae
{
	class GameObject;
	class Observer;
	struct Event;

	class Subject
	{
	public:
		virtual ~Subject() = default;
		virtual void AddObserver(std::shared_ptr<Observer> observer);
		virtual void RemoveObserver(std::shared_ptr<Observer> observer);
	protected:
		virtual void Notify(Event event, GameObject* actor);
	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};

}
