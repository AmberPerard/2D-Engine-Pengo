#include "GameCommands.h"

#include <iostream>

#include "BlocksManager.h"
#include "CharacterComponent.h"
#include "GameInfo.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceManager.h"

Move::Move(std::shared_ptr<dae::GameObject> pActor, glm::vec2 dir, int blocksize)
	: m_pActor(pActor),
	m_Dir(dir),
	m_Blocksize(blocksize)
{
}

void Move::Execute()
{
	glm::vec2 actorPos = m_pActor->GetTransform()->GetLocalPosition();
	float actorPosX = actorPos.x + (m_Dir.x * m_Blocksize);
	float actorPosY = actorPos.y + (m_Dir.y * m_Blocksize);
	m_pActor->GetTransform()->SetForwardVector(m_Dir);
	m_pActor->GetTransform()->SetPosition({ actorPosX, actorPosY });
}

Push::Push(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)
{
}

void Push::Execute()
{
	auto dir = m_pActor->GetTransform()->GetForwardVector();
	auto actorPos = m_pActor->GetTransform()->GetWorldPosition();
	glm::vec2 blocksize = GameInfo::GetInstance().GetBlockSize();
	glm::vec2 nextBlockOver = { actorPos.x + (blocksize.x * dir.x), actorPos.y + (blocksize.y * dir.y) };
	glm::vec2 nextBlockOver2 = { nextBlockOver.x + (blocksize.x * dir.x), nextBlockOver.y + (blocksize.y * dir.y) };
	auto blockToPush = BlocksManager::GetInstance().FindWall(nextBlockOver);
	if (blockToPush != nullptr)
	{
		auto blockNextToPushBlock = BlocksManager::GetInstance().FindWall(nextBlockOver2);
		if (!blockNextToPushBlock)
		{
			MovementDirection dirToPush = GameInfo::GetInstance().FindMovement(dir);
			blockToPush->EnableMovement(dirToPush);
		}
		else
		{
			blockToPush->BreakBlock();
		}
	}
}

Kill::Kill(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)
{
}

void Kill::Execute()
{
	m_pActor->GetComponent<CharacterComponent>()->Die();
}

CrushEnemy::CrushEnemy(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)
{
}

void CrushEnemy::Execute()
{
	m_pActor->GetComponent<CharacterComponent>()->GetCrushed();
}


void loadLevel();

void SwitchLevel::Execute()
{
	std::cout << "Switching level" << std::endl;
	switch (GameInfo::GetInstance().GetCurrentLevel())
	{
	case GameInfo::level1:
		GameInfo::GetInstance().SetCurrentLevel(GameInfo::level2);
		GameInfo::GetInstance().m_CurrentMap = GameInfo::GetInstance().maps[GameInfo::level2];
		loadLevel();
		break;
	case GameInfo::level2:
		GameInfo::GetInstance().SetCurrentLevel(GameInfo::level3);
		GameInfo::GetInstance().m_CurrentMap = GameInfo::GetInstance().maps[GameInfo::level3];
		loadLevel();
		break;
	case GameInfo::level3:
		GameInfo::GetInstance().SetCurrentLevel(GameInfo::level1);
		GameInfo::GetInstance().m_CurrentMap = GameInfo::GetInstance().maps[GameInfo::level1];
		loadLevel();
		break;
	}

}

void MuteAllSounds::Execute()
{
	m_Muted = !m_Muted;
	auto& ss = dae::ServiceManager::get_sound_system();
	if (m_Muted)
	{
		ss.UnpauseSound();
	}else
	{
		ss.PauseSound();
	}
}

HitEnemy::HitEnemy(std::shared_ptr<dae::GameObject> pActor)
	:m_pActor(pActor)

{

}

void HitEnemy::Execute()
{
	m_pActor->GetComponent<CharacterComponent>()->GetHit();
}