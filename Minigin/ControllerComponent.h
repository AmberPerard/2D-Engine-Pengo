#pragma once
#include "BaseComponent.h"

namespace dae
{


	class ControllerComponent  final : public BaseComponent
	{
	public:
		ControllerComponent(GameObject* gameObject);
		~ControllerComponent() override = default;
		ControllerComponent(const ControllerComponent& other) = delete;
		ControllerComponent(ControllerComponent&& other) = delete;
		ControllerComponent& operator=(const ControllerComponent& other) = delete;
		ControllerComponent& operator=(ControllerComponent&& other) = delete;

		void Update() override;
		void Render() override;
		void RenderUI() override;

		void SetControllerID(int id) { m_ControllerID = id; }
		int GetContollerID() const { return m_ControllerID; }

	private:
		int m_ControllerID{};
	};

}
