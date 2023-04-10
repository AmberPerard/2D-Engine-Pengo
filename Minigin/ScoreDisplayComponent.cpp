#include "ScoreDisplayComponent.h"

#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Observer.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* gameObject)
	:BaseComponent(gameObject), m_text("Score: 0")
{
	pTextComponent = gameObject->GetComponent<TextComponent>();
}

void dae::ScoreDisplayComponent::Update()
{
}

void dae::ScoreDisplayComponent::Render()
{
}

void dae::ScoreDisplayComponent::RenderUI()
{
}

void dae::ScoreDisplayComponent::OnNotify(EventType event, GameObject* actor)
{
	const auto owner = GetOwner()->GetComponent<CharacterComponent>();
	const auto otherActor = actor->GetComponent<CharacterComponent>();
	bool isPlayer = (actor->GetComponent<PlayerComponent>() != nullptr);
	bool isEnemy = (actor->GetComponent<EnemyComponent>() != nullptr);

	switch (event)
	{
	case PLAYER_DIED:
		if (isEnemy)
		{
			int newScore = otherActor->GetScore() + m_HighScore;
			m_text = "Score: " + std::to_string(newScore);
			owner->SetScore(newScore);
			pTextComponent->SetText(m_text);
		}
		break;
	case ENEMY_CRUSHED:
		if (isPlayer)
		{
			int newScore = otherActor->GetScore() + m_HighScore;
			m_text = "Score: " + std::to_string(newScore);
			owner->SetScore(newScore);
			pTextComponent->SetText(m_text);
		}
		break;
	case ENEMY_HIT:
		if (isPlayer)
		{
			int newScore = otherActor->GetScore() + m_LowScore;
			m_text = "Score: " + std::to_string(newScore);
			owner->SetScore(newScore);
			pTextComponent->SetText(m_text);
		}
		break;
	default:;
	}
}

void dae::ScoreDisplayComponent::SetScores(int lowScore, int Highscore)
{
	m_LowScore = lowScore;
	m_HighScore = Highscore;
}
