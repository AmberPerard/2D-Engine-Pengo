#include "CharacterComponent.h"

#include "BlockComponent.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Helpers.h"
#include "LivesDisplayComponent.h"
#include "Subject.h"

CharacterComponent::CharacterComponent(dae::GameObject* gameObject, dae::LivesDisplayComponent* livesDisplay)
	:BaseComponent(gameObject)
{
	m_CharacterSubject = std::make_unique<dae::Subject>();
	if (livesDisplay != nullptr)
	{
		m_CharacterSubject->AddObserver(livesDisplay);
	}

	if(GetOwner()->GetComponent<dae::ColliderComponent>())
	{
		dae::ColliderComponent::CollisionCallback callback = [&](dae::GameObject* hit) { this->OnCollision(hit); };
		GetOwner()->GetComponent<dae::ColliderComponent>()->SetCollisionCallback(callback);
	}
}

void CharacterComponent::Update()
{
}

void CharacterComponent::FixedUpdate()
{

}

void CharacterComponent::Render()
{
}

void CharacterComponent::RenderUI()
{
}

void CharacterComponent::OnCollision(dae::GameObject* otherCollider)
{
	if (otherCollider->GetComponent<BlockComponent>())
	{
		auto size = otherCollider->GetComponent<dae::ColliderComponent>()->GetSize();
		auto transform = GetOwner()->GetTransform();
		glm::vec2 lastDirection  = transform->GetForwardVector();
		otherCollider->GetComponent<dae::ColliderComponent>()->EnableDebug();
		transform->SetPosition(transform->GetLocalPosition().x + (size.x * -(lastDirection.x)), transform->GetLocalPosition().y + (size.y * -(lastDirection.y)));
	}
}

void CharacterComponent::Die()
{
	int lives = GetLives();
	SetLives(--lives);
	m_CharacterSubject->Notify(PLAYER_DIED, this->GetOwner());
	if (GetLives() < 0)
	{
		m_CharacterSubject->Notify(PLAYER_LOST, this->GetOwner());
	}
}

void CharacterComponent::GetCrushed()
{
	m_CharacterSubject->Notify(ENEMY_CRUSHED, this->GetOwner());
	if (GetLives() <= 0)
	{
		Die();
	}
}

void CharacterComponent::GetHit()
{
	m_CharacterSubject->Notify(ENEMY_HIT, this->GetOwner());
	if (GetLives() <= 0)
	{
		Die();
	}
}

void CharacterComponent::AddObserver(dae::Observer* observer)
{
	m_CharacterSubject->AddObserver(observer);
	Start();
}

void CharacterComponent::Start()
{
	m_CharacterSubject->Notify(LEVEL_STARTED, this->GetOwner());
}