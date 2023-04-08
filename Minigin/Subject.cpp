#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void dae::Subject::Notify(Event event, GameObject* actor)
{
	for (std::shared_ptr<Observer> observer : m_Observers)
		observer->OnNotify(event, actor);
}
