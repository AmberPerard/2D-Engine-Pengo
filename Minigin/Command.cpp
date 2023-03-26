#include "Command.h"

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"

dae::Command::Command(std::shared_ptr<GameObject> object)
	:object(object)
{
}

dae::Move::Move(std::shared_ptr<GameObject> object)
	:Command(object)
{
}

void dae::Move::Execute()
{
	glm::vec2 moveInput = InputManager::GetInstance().GetController(0)->GetLeftThumbStick();
	glm::vec3 actorPos = GetObject()->GetTransform()->GetLocalPosition();
	float actorPosX = actorPos.x + moveInput.x;
	float actorPosY = actorPos.y + moveInput.y;
	GetObject()->GetTransform()->SetPosition(actorPosX, actorPosY);
}
