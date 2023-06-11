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

        std::shared_ptr<Scene> GetScene(std::string name);
        void AddScene (std::shared_ptr<Scene> scene);
    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;
        std::vector<std::shared_ptr<Scene>> m_pScenes{};
        std::shared_ptr<Scene> m_pActiveScene{};
	};
}
