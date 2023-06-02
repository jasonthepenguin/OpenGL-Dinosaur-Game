
#include "EngGUI.h"

#include <GLFW/glfw3.h>
#include "LabEngine.h"




EngGUI::EngGUI()
{
	m_PixelsGLFWWindow = LabEngine::getInstance().m_window->m_PixelsGLFWWindow;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL;

	// Set ImGui style
	ImGui::StyleColorsDark();

	// Initialize ImGui GLFW and OpenGL bindings
	ImGui_ImplGlfw_InitForOpenGL(m_PixelsGLFWWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");


	TextureFactory textFact;
	// -- INIT PHOTO FOR GUI
	auto groupPhoto = textFact.createTexture("group_photo.png");
	groupPhoto->load();

	image_texture_id = groupPhoto->texture;

}


EngGUI::~EngGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


void EngGUI::BeginFrame()
{

	//auto window = LabEngine::getInstance().m_window->window;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	if (show_demo_window) {
		//ImGui::SetNextWindowSize(ImVec2(300, 200)); // Set the window size 
		ImGui::SetNextWindowSize(ImVec2(300, 300)); // Set the window size

		// ImGui content goes here, e.g.:
		ImGui::Begin("Welcome to our Demo! (pls have mercy)");
		ImGui::Text("- Press M to open and close this manual!");
		ImGui::Text("- Press K to go into wireframe mode!");
		ImGui::Text("- Press X to quit this demo!");
		ImGui::Text("- Press WASD keys to move!");
		ImGui::Text("- Press Space key to spawn boxes (test)");
		ImGui::Text("- Press the F key to fly!");
		ImGui::Text("- Use the mouse to look!");
		ImGui::Text("\n");
		ImGui::Text("Player Score : %d", LabEngine::getInstance().ourGameData.score);
		ImGui::End();

		if (show_image) {
			glfwSetInputMode(m_PixelsGLFWWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			//ImVec2 image_size(groupPhoto->width, groupPhoto->height); // Set the image display size to 300x200
			ImVec2 image_size(1000, 700); // Set the image display size to 300x200
			ImGui::Begin("Image Display");
			ImGui::Image((void*)(intptr_t)image_texture_id, image_size, ImVec2(0, 1), ImVec2(1, 0));
			if (ImGui::IsItemClicked()) {
				glfwSetWindowShouldClose(m_PixelsGLFWWindow, true);
			}
			ImGui::End();
		}


	}

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Save")) {
				save_game();
			}
			if (ImGui::MenuItem("Load")) {
				load_game();
			}
			if (ImGui::MenuItem("Quit")) {
				//glfwSetWindowShouldClose(window, true);
				LabEngine::getInstance().m_window->shouldClose();
				//std::cout << "Button pressed!" << std::endl;
				exit(0);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

}

void EngGUI::save_game() {
	std::ofstream outfile("savegame.txt");
	outfile << LabEngine::getInstance().ourGameData.score << std::endl;
	outfile.close();
}

void EngGUI::load_game() {
	std::ifstream infile("savegame.txt");
	infile >> LabEngine::getInstance().ourGameData.score;
	infile.close();
}


void EngGUI::EndFrame() {

	ImGui::Render();

}

void EngGUI::renderData()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // doing this at the end so draws on top of everything else
}


void EngGUI::MainMenu(){

}