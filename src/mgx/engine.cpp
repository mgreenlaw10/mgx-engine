#include "mgx/engine.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>

// GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// Project misc.
#include "error.hpp"

// MGX
#include "mgx/vao.hpp"
#include "mgx/vbo.hpp"
#include "mgx/ibo.hpp"
#include "mgx/blo.hpp"
#include "mgx/renderer.hpp"
#include "mgx/camera.hpp"

// Scenes
#include "scene/scene.hpp"
#include "scene/scene_manager.hpp"
#include "scene/scene_home_menu.hpp"
#include "scene/scene_quad_test.hpp"
#include "scene/scene_cube.hpp"

namespace mgx {

	Engine* Engine::static_instance = nullptr;

	Engine::Engine() {}

	Engine* Engine::GetInstance() {
		if (static_instance == nullptr)
			static_instance = new Engine();
		return static_instance;
	}

	void Engine::InitGLFW() {
		if (!glfwInit()) 
	        ExitWithError(GLFW_INIT_FAIL);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);    
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	    window = mgx::Window(glfwCreateWindow(1200, 900, "MAIN", NULL, NULL));

	    if (!window.GetGLFWwindow()) {
	        glfwTerminate();
	        ExitWithError(WINDOW_INIT_FAIL);
	    }
	    glfwMakeContextCurrent(window.GetGLFWwindow());
	    glfwSwapInterval(1);

	    GLCall( glViewport(0, 0, 1200, 900) );
	    GLCall( glEnable(GL_BLEND) );
	    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
	}

	void Engine::InitGLEW() {
		if (glewInit() != GLEW_OK) 
        	ExitWithError(GLEW_INIT_FAIL);
	}

	void Engine::InitIMGUI() {
		IMGUI_CHECKVERSION();
    	ImGui::CreateContext();
    	ImGui::StyleColorsDark();
    
	    ImGui_ImplOpenGL3_Init();
	    ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWwindow(), true);

	    ImGuiIO& io = ImGui::GetIO();
	    (void)io;
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	}

	void Engine::Start() {

	    mgx::SceneMenu* menu = new mgx::SceneMenu();
	    menu->RegisterScene<mgx::SceneQuadTest>("DrawQuad Test");
	    menu->RegisterScene<mgx::SceneCube>("Cube");

	    SceneManager::GetInstance()->SetHomeScene(menu);
	    SceneManager::GetInstance()->GoHome();

	    menu = nullptr;
	    
	    /***********************************************/
	    while (!glfwWindowShouldClose(window.GetGLFWwindow())) {

	        SceneManager::GetInstance()->GetCurrentScene()->GetRenderer().Clear();

	        ImGui_ImplOpenGL3_NewFrame();
	        ImGui_ImplGlfw_NewFrame();
	        ImGui::NewFrame();

	        if (SceneManager::GetInstance()->GetCurrentScene()) {
	            SceneManager::GetInstance()->GetCurrentScene()->OnUpdate(0.0f);
	            SceneManager::GetInstance()->GetCurrentScene()->OnRender();
	            SceneManager::GetInstance()->GetCurrentScene()->OnImGuiRender();

	            if (SceneManager::GetInstance()->AtHome() == false) {        
	                SceneManager::GetInstance()->DisplayHomeButton();
	            }
	        }
	        ImGui::Render();
	        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	        
	        glfwSwapBuffers(window.GetGLFWwindow());
	        glfwPollEvents();
	    }
	    End();
	}

	void Engine::End() {
		ImGui_ImplOpenGL3_Shutdown();
	    ImGui_ImplGlfw_Shutdown();

	    ImGui::DestroyContext();
	    glfwTerminate();
	}
}

