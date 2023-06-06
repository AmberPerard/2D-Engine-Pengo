#include "ColliderComponent.h"

#include "CollisionManager.h"
#include "Renderer.h"

dae::ColliderComponent::ColliderComponent(GameObject* pGameObject)
	:BaseComponent(pGameObject),
	m_Size({ 0,0 })

{
	CollisionManager::GetInstance().Add(this);
}

dae::ColliderComponent::~ColliderComponent()
{
	CollisionManager::GetInstance().Remove(this);
}

void dae::ColliderComponent::Update()
{
}

void dae::ColliderComponent::FixedUpdate()
{
}

void dae::ColliderComponent::Render()
{
	if (m_IsDebug)
	{
		auto pos = this->GetOwner()->GetTransform()->GetWorldPosition();
		auto rect = SDL_Rect{ int(pos.x),int(pos.y) , int(m_Size.x),int(m_Size.y) };
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 0);
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	}
}

void dae::ColliderComponent::RenderUI()
{
}

glm::vec3 dae::ColliderComponent::GetOwnerPosition() const
{
	return this->GetOwner()->GetTransform()->GetWorldPosition();
}

void dae::ColliderComponent::OnCollision(ColliderComponent* other)
{
	if (m_CollisionCallback)
	{
		m_CollisionCallback(other->GetOwner());
	}
}
