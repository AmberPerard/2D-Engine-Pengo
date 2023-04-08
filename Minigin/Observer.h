#pragma once
namespace dae
{
	class GameObject;

	//bad for bigger games, but i think okay for my case?
	enum EventType {
		LEVEL_STARTED,
		PLAYER_SPAWNED,
		PLAYER_HIT,
		PLAYED_DIED,
		PLAYER_GAINED_SCORE

	};

	struct Event {

		EventType m_type;

	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Event event, GameObject* actor) = 0;
	};
}
