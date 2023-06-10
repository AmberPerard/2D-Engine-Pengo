#include "GameInfo.h"

MovementDirection GameInfo::FindMovement(glm::vec2 input)
{
	for (auto direction : DirectionMap)
	{
		if (direction.second == input)
		{
			return direction.first;
		}
	}
	return MovementDirection::NONE;
}
