#pragma once

#include <functional>
#include <vector>
#include <string>
#include <memory>

// Project globals
#include <global_consts.hpp>

// GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// mgx
#include "mgx/renderer.hpp"
#include "mgx/key_handler.hpp"

// ImGui
#include <IMGUI/imgui.h>

// GLEW/GLFW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mgx {

	class Scene {
	protected:
		mgx::Renderer renderer;
		mgx::KeyHandler keyHandler;

	public:
		
		Scene(const mgx::Camera3D& camera): renderer(camera) {}

		virtual ~Scene() {}

		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

		virtual void OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {}
		virtual void OnMouseMotionInput(GLFWwindow* window, double xpos, double ypos) {}
		virtual void OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods) {}

		inline mgx::Renderer& GetRenderer() {return renderer;}
	};
};