#include <scene/scene_quad_test.hpp>

#include <mgx/texture.hpp>

#include "mgx/engine.hpp"
#include "mgx/key_handler.hpp"

#include <iostream>

namespace mgx {

	SceneQuadTest::SceneQuadTest() : Scene(mgx::Camera3D()) {
		tex = new mgx::texture();
		tex->LoadFromFile("res/texture/lucki.png");

		pos_initialized = false;

		keyHandler.DefineWhilePressed(GLFW_KEY_W, [this]() {
			renderer.GetCamera().MoveForward(0.1f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_S, [this]() {
			renderer.GetCamera().MoveForward(-0.1f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_D, [this]() {
			renderer.GetCamera().Strafe(0.1f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_A, [this]() {
			renderer.GetCamera().Strafe(-0.1f);
		});
	}

	SceneQuadTest::~SceneQuadTest() {
		delete tex;
		delete[] pos1;
		delete[] pos2;
	}

	void SceneQuadTest::OnUpdate(float dt) {
		keyHandler.ProcessKeyState();
	}

	void SceneQuadTest::OnRender() {
		GLCall( glDisable(GL_DEPTH_TEST) );
		GLCall( glClearColor(0.6f, 0.6f, 1.0f, 1.0f) );
		GLCall( glClear(GL_COLOR_BUFFER_BIT) );

		renderer.DrawQuadCC		(pos1[0], pos1[1], pos1[2], pos1[3], pos1[4]);
		renderer.DrawQuadTexture(pos2[0], pos2[1], pos2[2], pos2[3], pos2[4], *tex);
	}

	void SceneQuadTest::OnImGuiRender() {
		int window_w, window_h;
		glfwGetWindowSize(Engine::GetInstance()->GetWindow(), &window_w, &window_h);

		if (!pos_initialized) {
			int gui_w = 400;
			int gui_h = 300;
			ImGui::SetNextWindowPos (ImVec2(window_w - gui_w - 30, 30));
			ImGui::SetNextWindowSize(ImVec2(gui_w, gui_h));
			pos_initialized = true;
		}
		ImGui::Begin("test", NULL, ImGuiWindowFlags_NoResize);

	    ImGui::SliderFloat("x1", &pos1[0], -1.0f, 1.0f, "%0.1f");
	    ImGui::SliderFloat("y1", &pos1[1], -1.0f, 1.0f, "%0.1f");
	    ImGui::SliderFloat("z1", &pos1[2], -10.0f, 10.0f, "%0.1f");

	    ImGui::SliderFloat("x2", &pos2[0], -1.0f, 1.0f, "%0.1f");
	    ImGui::SliderFloat("y2", &pos2[1], -1.0f, 1.0f, "%0.1f");
	    ImGui::SliderFloat("z2", &pos2[2], -10.0f, 10.0f, "%0.1f");

	    ImGuiIO& io = ImGui::GetIO(); (void)io;
	    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

	    ImGui::End();

	    // Camera test
	    ImGui::Begin("camera test");

	    ImGui::Text("Camera pos: %.2f, %.2f, %.2f", renderer.GetCamera().GetPosition().x,
	    											renderer.GetCamera().GetPosition().y,
	    											renderer.GetCamera().GetPosition().z);

	    ImGui::Text("Camera dir: %.2f, %.2f, %.2f", renderer.GetCamera().GetDirection().x,
	    											renderer.GetCamera().GetDirection().y,
	    											renderer.GetCamera().GetDirection().z);

	    ImGui::End();
	}

	void SceneQuadTest::OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyHandler.UpdateKeyState(key, action, mods);
	}

	void SceneQuadTest::OnMouseMotionInput(GLFWwindow* window, double xpos, double ypos) {

	}

	void SceneQuadTest::OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods) {

	}


}

