#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
        void LoadScene(std::shared_ptr<Scene> scene);

        void Update();
        void FixedUpdate();
        void Render();
        void RenderUI();
    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;
        std::shared_ptr<Scene> m_pActiveScene{};
	};
}
