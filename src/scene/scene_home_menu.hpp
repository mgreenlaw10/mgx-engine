#pragma once

#include <scene/scene.hpp>
#include <scene/scene_manager.hpp>

namespace mgx
{
	class SceneMenu : public Scene {
	public:

		SceneMenu() : Scene(mgx::Camera3D()) {}

		void OnUpdate(float dt);
		void OnRender();
		void OnImGuiRender();

		template <typename T>
		void RegisterScene(const std::string& name) {
			m_Scenes.push_back(std::make_pair(name, [](){ return new T(); }));
		}

	private:
		std::vector<std::pair<std::string, std::function<Scene*()>>> m_Scenes;
	};
}