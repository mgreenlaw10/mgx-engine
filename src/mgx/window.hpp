#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace mgx {

	class Window {
	private:
		GLFWwindow* window_ptr;

	public:

		inline Window(): window_ptr(nullptr) {}

		inline Window(GLFWwindow* window): window_ptr(window) {}

		inline GLFWwindow* GetGLFWwindow() {return window_ptr;}

	};
}