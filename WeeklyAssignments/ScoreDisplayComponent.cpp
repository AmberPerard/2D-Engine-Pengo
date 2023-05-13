#include "ScoreDisplayComponent.h"

#include "CharacterComponent.h"
#include "EventTypes.h"
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

void dae::ScoreDisplayComponent::OnNotify(int event, GameObject* actor)
{
	const auto actorCharacterComp = actor->GetComponent<CharacterComponent>();
	int newScore{ };
	switch (event)
	{
	case PLAYER_DIED:

			newScore = actorCharacterComp->GetScore() + m_HighScore;
			m_text = "Score: " + std::to_string(newScore);
			actorCharacterComp->SetScore(newScore);
			pTextComponent->SetText(m_text);

		break;
	case ENEMY_CRUSHED:

			newScore = actorCharacterComp->GetScore() + m_HighScore;
			m_text = "Score: " + std::to_string(newScore);
			actorCharacterComp->SetScore(newScore);
			pTextComponent->SetText(m_text);

		break;
	case ENEMY_HIT:
			newScore = actorCharacterComp->GetScore() + m_LowScore;
			m_text = "Score: " + std::to_string(newScore);
			actorCharacterComp->SetScore(newScore);
			pTextComponent->SetText(m_text);
		break;
	default:;
	}
}

void dae::ScoreDisplayComponent::SetScores(int lowScore, int Highscore)
{
	m_LowScore = lowScore;
	m_HighScore = Highscore;
}
