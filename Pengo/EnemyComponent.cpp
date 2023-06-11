#include "EnemyComponent.h"

#include "BlockComponent.h"
#include "CharacterComponent.h"
#include "ColliderComponent.h"
#include "EnemyManager.h"
#include "GameInfo.h"

EnemyComponent::EnemyComponent(dae::GameObject* gameObject)
	:BaseComponent(gameObject)
{
	EnemyManager::GetInstance().AddEnemy(this);

	if (GetOwner()->GetComponent<dae::ColliderComponent>())
	{
		dae::ColliderComponent::CollisionCallback callback = [&](dae::GameObject* hit) { this->OnCollision(hit); };
		GetOwner()->GetComponent<dae::ColliderComponent>()->SetCollisionCallback(callback);
	}
}

EnemyComponent::~EnemyComponent()
{
	EnemyManager::GetInstance().RemoveEnemy(this);
}

void EnemyComponent::Update()
{

}

void EnemyComponent::FixedUpdate()
{

}

void EnemyComponent::Render()
{

}

void EnemyComponent::RenderUI()
{

}

void EnemyComponent::OnCollision(dae::GameObject* otherCollider)
{
	auto block = otherCollider->GetComponent<BlockComponent>();
	if (block != nullptr)
	{
		if (block->IsMoving())
		{
			Die();
			//follow the movement untill you hit a non moving wall on the other side
		}
		else
		{
			glm::vec2 lastDirection = GetOwner()->GetTransform()->GetForwardVector();
			const auto otherCol = block->GetColumn();
			const auto otherRow = block->GetRow();

			const auto newCol = otherCol + (1 * -int(lastDirection.x));
			const auto newRow = otherRow + (1 * -int(lastDirection.y));

			const auto newPosX = newCol * GameInfo::GetInstance().GetBlockSize().x + GameInfo::GetInstance().GetPlayFieldOffset().x;
			const auto newPosY = newRow * GameInfo::GetInstance().GetBlockSize().y + GameInfo::GetInstance().GetPlayFieldOffset().y;

			GetOwner()->GetTransform()->SetPosition(glm::vec2{ newPosX, newPosY });
			m_CurrentDirection = static_cast<MovementDirection>(rand() % 4);
		}
	}

	auto character = otherCollider->GetComponent<CharacterComponent>();
	if (character != nullptr)
	{
		//do only once cause now infinite
		//character->Die();
	}
}

void EnemyComponent::Start()
{
	m_CurrentDirection = static_cast<MovementDirection>(rand() % 4);
}

void EnemyComponent::Die()
{
	GetOwner()->Delete();
}
