#pragma once
#include <memory>
#include <vector>

#include "Observer.h"

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		virtual ~Subject() = default;
		virtual void AddObserver(Observer* observer);
		virtual void RemoveObserver(Observer* observer);
		virtual void Notify(EventType event, GameObject* actor);
	private:
		std::vector<Observer*> m_Observers;
	};

}
