#pragma once

#include "scene/scene.hpp"
#include "scene/scene_manager.hpp"

#include "mgx/vao.hpp"
#include "mgx/vbo.hpp"
#include "mgx/ibo.hpp"
#include "mgx/blo.hpp"
#include "mgx/shader.hpp"
#include "mgx/texture.hpp"
#include "mgx/mesh.hpp"
#include "mgx/engine.hpp"

#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

namespace mgx {
	class SceneCube : public Scene {
	private:
		// basically a vao reference
		mgx::CubeM cubem;

		// cursor mode
		bool cursorEnabled = true;

		// data applied when drawing a mesh vao
		std::vector <mgx::MeshInstance> meshes = {
		    {glm::vec3( 0.0f, 0.0f,  0.0f), glm::vec3(10.0f, 1.0f, 10.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0}
		};

		std::vector<mgx::MeshInstance> color_cubes = {
			{glm::vec3( 1.0f, 1.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 2.0f, 1.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 3.0f, 1.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 4.0f, 1.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 5.0f, 1.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0},

			{glm::vec3( 1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 2.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 3.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 4.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
			{glm::vec3( 5.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}
		};

		mgx::texture textures[3] = { // texture binding wont work with vectors
			{"res/texture/lucki.png"},
			{"res/texture/ivern.png"},
			{"res/texture/acid.jpg"}
		};

		std::vector<glm::vec4> colors = {
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		};


	public:
		SceneCube();
		~SceneCube();

		void OnUpdate(float dt);
		void OnRender();
		void OnImGuiRender();

		void OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		void OnMouseMotionInput(GLFWwindow* window, double xpos, double ypos);
		void OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods);
	};
}