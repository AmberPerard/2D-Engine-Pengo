#pragma once
namespace dae
{
	class GameObject;

	//bad for bigger games, but i think okay for my case?
	enum EventType {
		LEVEL_STARTED,
		PLAYER_SPAWNED,
		PLAYER_HIT,
		PLAYER_DIED,
		PLAYER_GAINED_SCORE,
		PLAYER_LOST,
		ENEMY_CRUSHED,
		ENEMY_HIT,
		ENEMY_DIED,

	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(EventType event, GameObject* actor) = 0;
	};
}
