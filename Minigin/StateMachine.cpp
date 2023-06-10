#include "StateMachine.h"

#include "BaseState.h"

dae::StateMachine::StateMachine(GameObject* gameObject)
	:BaseComponent(gameObject)
{
}

void dae::StateMachine::Initialize(std::unique_ptr<BaseState> startState)
{
	m_state = std::move(startState);
	m_state->Enter(GetOwner());
}

void dae::StateMachine::Update()
{
	std::unique_ptr<BaseState> state = m_state->Update(GetOwner());

	if (state != nullptr)
	{
		m_state->Exit(GetOwner());

		m_state = std::move(state);
		m_state->Enter(GetOwner());
	}
}

void dae::StateMachine::FixedUpdate()
{
	m_state->FixedUpdate(GetOwner());
}

void dae::StateMachine::Render()
{
}

void dae::StateMachine::RenderUI()
{
}

void dae::StateMachine::SetState(std::unique_ptr<BaseState> state)
{
	m_state->Exit(GetOwner());
	m_state = std::move(state);
	m_state->Enter(GetOwner());
}
