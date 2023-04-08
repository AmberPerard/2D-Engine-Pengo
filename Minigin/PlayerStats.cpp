#include "PlayerStats.h"
#include "Observer.h"

void dae::PlayerStats::OnNotify(Event event, GameObject* actor)
{
	switch (event)
	{

	case PLAYED_DIED:
		m_Lives --;
		break;
	case PLAYER_GAINED_SCORE:
		m_Score += 100;
		break;

	}
}
