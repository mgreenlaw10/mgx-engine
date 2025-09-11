#include <scene/scene_home_menu.hpp>

#include "mgx/engine.hpp"

#include <GLFW/glfw3.h>

namespace mgx {

	void SceneMenu::OnUpdate(float dt) {}

	void SceneMenu::OnRender() {
		GLCall( glClearColor(0.6f, 0.6f, 1.0f, 1.0f) );
		GLCall( glClear(GL_COLOR_BUFFER_BIT) );
	}

	void SceneMenu::OnImGuiRender() {
		int window_w, window_h;
		glfwGetWindowSize(Engine::GetInstance()->GetWindow(), &window_w, &window_h);

		ImGui::SetNextWindowPos(ImVec2(window_w * 0.5f, window_h * 0.5f), 0, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(window_w * 0.5f, window_h * 0.5f));
		ImGui::Begin("HOME MENU", NULL,
			ImGuiWindowFlags_NoResize | 
			ImGuiWindowFlags_NoTitleBar | 
			ImGuiWindowFlags_NoMove );
        ImGui::Text("Choose a scene:");

		for (auto& scene : m_Scenes) {
			if (ImGui::Button(scene.first.c_str()))
				SceneManager::GetInstance()->SetCurrentScene(scene.second());
		}
		ImGui::End();
	}
};