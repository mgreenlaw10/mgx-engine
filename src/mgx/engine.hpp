#pragma once

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

// GLEW/GLFW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ImGUI
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

// MGX
#include "mgx/window.hpp"
#include "scene/scene_manager.hpp"

//
//	GLFW input callbacks: every time there is an input, tell the active scene then tell ImGui
//

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	SceneManager::GetInstance()->GetCurrentScene()->OnKeyInput	(window, key, scancode, action, mods);
	ImGui_ImplGlfw_KeyCallback									(window, key, scancode, action, mods);
}

static void MousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	SceneManager::GetInstance()->GetCurrentScene()->OnMouseMotionInput	(window, xpos, ypos);
    ImGui::GetIO().AddMousePosEvent										((float)xpos, (float)ypos);
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	SceneManager::GetInstance()->GetCurrentScene()->OnMouseButtonInput	(window, button, action, mods);
	ImGui_ImplGlfw_MouseButtonCallback									(window, button, action, mods);
}

static void  WindowResizeCallback(GLFWwindow* window, int width, int height) {
	SceneManager::GetInstance()->GetCurrentScene()->GetRenderer().SetVPDimension(width, height);
}

//
//	Engine class (singleton) represents global state
//

namespace mgx {

	class Engine {
	private:
		static Engine* static_instance;
		Engine();

		mgx::Window window;

	public:

		static Engine* GetInstance();

		void InitGLFW();
		void InitGLEW();
		void InitIMGUI();

		inline void Init() {
			InitGLFW();
			InitGLEW();
			InitIMGUI();

			glfwSetKeyCallback				(window.GetGLFWwindow(), KeyCallback);
			glfwSetCursorPosCallback		(window.GetGLFWwindow(), MousePosCallback);
			glfwSetMouseButtonCallback		(window.GetGLFWwindow(), MouseButtonCallback);
			glfwSetFramebufferSizeCallback	(window.GetGLFWwindow(), WindowResizeCallback);
		}

		void Start();
		void End();

		inline GLFWwindow* GetWindow() {return window.GetGLFWwindow();}
	};
}