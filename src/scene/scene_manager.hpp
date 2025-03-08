 #pragma once

#include <scene/scene.hpp>

#include <memory>

class SceneManager {
private:
	static SceneManager* static_instance;

public:
	static SceneManager* GetInstance();

	void SetCurrentScene(mgx::Scene* new_scene);
	inline mgx::Scene* GetCurrentScene() const {
		return current_scene.get();
	}

	void SetHomeScene(mgx::Scene* new_scene);
	inline mgx::Scene* GetHomeScene() const {
		return home_scene.get();
	}

	void GoHome();
	bool AtHome();

	void DisplayHomeButton();

private:
	std::shared_ptr<mgx::Scene> current_scene;
	std::shared_ptr<mgx::Scene> home_scene;
};

