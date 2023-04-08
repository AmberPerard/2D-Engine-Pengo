#pragma once
#include "Observer.h"

namespace dae
{

	class PlayerStats : public Observer
	{
	public:
		void OnNotify(Event event, GameObject* actor) override;
	private:
		int m_Score{ 0 };
		int m_Lives{ 3 };
	};

}
