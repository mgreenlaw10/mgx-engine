#include <scene/scene_cube.hpp>

namespace mgx {

	SceneCube::SceneCube() : Scene(mgx::Camera3D({0.0f, 1.0f, 3.0f}, {0.0f, 1.0f, 0.0f}))
	{
		// WASD
		keyHandler.DefineWhilePressed(GLFW_KEY_W, [this]()
		{
			renderer.GetCamera().MoveForward(0.05f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_S, [this]()
		{
			renderer.GetCamera().MoveForward(-0.05f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_D, [this]()
		{
			renderer.GetCamera().Strafe(0.05f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_A, [this]()
		{
			renderer.GetCamera().Strafe(-0.05f);
		});

		// SPACE/SHIFT
		keyHandler.DefineWhilePressed(GLFW_KEY_SPACE, [this]()
		{
			renderer.GetCamera().MoveUp(0.05f);
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_LEFT_SHIFT, [this]()
		{
			renderer.GetCamera().MoveUp(-0.05f);
		});

		// ARROW KEYS
		keyHandler.DefineWhilePressed(GLFW_KEY_UP, [this]()
		{
			renderer.GetCamera().Pitch(glm::radians(1.0f));
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_DOWN, [this]()
		{
			renderer.GetCamera().Pitch(glm::radians(-1.0f));
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_RIGHT, [this]()
		{
			renderer.GetCamera().Yaw(glm::radians(-1.0f));
		});
		keyHandler.DefineWhilePressed(GLFW_KEY_LEFT, [this]()
		{
			renderer.GetCamera().Yaw(glm::radians(1.0f));
		});
	}

	SceneCube::~SceneCube() {}

	void SceneCube::OnUpdate(float dt) {
		keyHandler.ProcessKeyState();
	}

	void SceneCube::OnRender() {
		GLCall( glClearColor(0.6f, 0.6f, 1.0f, 1.0f) );
		GLCall( glEnable(GL_DEPTH_TEST) );
		GLCall( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );

		renderer.DrawMeshes(cubem.vao, meshes, 3, textures, 3);
	}

	void SceneCube::OnImGuiRender() {
		// Camera test
	    ImGui::Begin("camera test");

	    ImGui::Text("Camera pos: (x=%.2f, y=%.2f, z=%.2f)", renderer.GetCamera().GetPosition().x,
	    													renderer.GetCamera().GetPosition().y,
	    													renderer.GetCamera().GetPosition().z );

	    ImGui::Text("Camera dir: (x=%.2f, y=%.2f, z=%.2f)", renderer.GetCamera().GetDirection().x,
	    													renderer.GetCamera().GetDirection().y,
	    													renderer.GetCamera().GetDirection().z );

	    ImGui::End();
	}

	void SceneCube::OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyHandler.UpdateKeyState(key, action, mods);
	}

	void SceneCube::OnMouseMotionInput(GLFWwindow* window, double xpos, double ypos) {

	}

	void SceneCube::OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods) {

	}


}