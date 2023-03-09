#pragma once
namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pGameObject);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void Render() = 0;

		void Delete() { m_MarkedForDeletion = true; }
		bool IsMarkedForDeletion() const { return m_MarkedForDeletion; }

	protected:
		GameObject* GetOwner() const { return m_pGameObject; }
	private:
		GameObject* m_pGameObject{ nullptr };
		bool m_MarkedForDeletion{ false };
	};
}


