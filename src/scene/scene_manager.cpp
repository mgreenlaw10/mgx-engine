#include <scene/scene_manager.hpp>

#include <IMGUI/imgui.h>

SceneManager* SceneManager::static_instance = nullptr;

SceneManager* SceneManager::GetInstance() {
	if (static_instance == nullptr)
		return static_instance = new SceneManager();
	return static_instance;
}

// ONLY called with new() ptr
void SceneManager::SetCurrentScene(mgx::Scene* new_scene) {
	current_scene = std::shared_ptr<mgx::Scene>(new_scene);
}

// ONLY called with new() ptr
void SceneManager::SetHomeScene(mgx::Scene* new_scene) {
	home_scene = std::shared_ptr<mgx::Scene>(new_scene);
}

void SceneManager::GoHome() {
	current_scene = home_scene;
}

bool SceneManager::AtHome() {
	return (current_scene == home_scene);
}

void SceneManager::DisplayHomeButton() {
	const unsigned int home_button_w = 100;
	const unsigned int home_button_h = 20;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(home_button_w, home_button_h));
	ImGui::Begin("HOME BUTTON", NULL,   
		ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoBackground );
    if (ImGui::Button("<- GO HOME"))
        SceneManager::GetInstance()->GoHome();
    ImGui::End();
}
