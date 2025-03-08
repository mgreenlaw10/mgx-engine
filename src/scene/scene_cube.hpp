#pragma once

#include <scene/scene.hpp>
#include <scene/scene_manager.hpp>

#include <global_consts.hpp>

#include <mgx/vao.hpp>
#include <mgx/vbo.hpp>
#include <mgx/ibo.hpp>
#include <mgx/blo.hpp>
#include <mgx/shader.hpp>
#include <mgx/texture.hpp>

#include <memory>

#include "mgx/mesh.hpp"

namespace mgx {
	class SceneCube : public Scene {
	private:
		// basically a vao reference
		mgx::CubeM cubem;

		// data applied when drawing a mesh vao
		mgx::MeshInstance meshes[7] = {

			// floor
		    {glm::vec3( 0.0f, 0.0f,  0.0f), glm::vec3(50.0f, 1.0f, 50.0f), glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0}, 

		    // {glm::vec3( 2.0f, 1.0f, -4.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0}, 
		    // {glm::vec3( 2.0f, 1.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0},
		    {glm::vec3( 2.0f, 1.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 2},
		    // {glm::vec3( 2.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0},
		    // {glm::vec3( 2.0f, 1.0f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0},
		    {glm::vec3(-1.0f, 1.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1}
		};

		// textures with indices corresponding to a mesh instance texture attribute
		mgx::texture textures[3] = {
			{"res/texture/lucki.png"},
			{"res/texture/ivern.png"},
			{"res/texture/acid.jpg"}
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