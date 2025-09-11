#pragma once

#include <scene/scene.hpp>
#include <scene/scene_manager.hpp>

#include <mgx/vao.hpp>
#include <mgx/vbo.hpp>
#include <mgx/ibo.hpp>
#include <mgx/blo.hpp>
#include <mgx/shader.hpp>
#include <mgx/texture.hpp>

#include <memory>


#include "mgx/engine.hpp"

namespace mgx {
	class SceneQuadTest : public Scene {
	public:
		SceneQuadTest();
		~SceneQuadTest();

		void OnUpdate(float dt);
		void OnRender();
		void OnImGuiRender();

		void OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		void OnMouseMotionInput(GLFWwindow* window, double xpos, double ypos);
		void OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods);

	private:
		bool pos_initialized;

		mgx::texture* tex;

		float* pos1 = new float[5]{-0.2f, -0.2f, 0.0f, 1.0f, 1.0f};
		float* pos2 = new float[5]{-0.5f, -0.5f, 0.0f, 1.0f, 1.0f};
	};
}