#pragma once
#include <string>

#include "BaseComponent.h"
#include "Observer.h"
namespace dae
{
	class TextComponent;

class ScoreDisplayComponent final : public BaseComponent, public Observer
{
public:
	ScoreDisplayComponent(GameObject* gameObject);
	~ScoreDisplayComponent() override = default;
	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	void Update() override;
	void Render() override;
	void RenderUI() override;

	void OnNotify(EventType event, GameObject* actor) override;
	void SetScores(int lowScore, int Highscore = 400);

private:
	TextComponent* pTextComponent;
	std::string m_text;

	int m_LowScore{ 100 };
	int m_HighScore{ 400 };
};

}
