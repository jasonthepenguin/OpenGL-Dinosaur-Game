
#include "EngGUI.h"

#include <GLFW/glfw3.h>
#include "LabEngine.h"


#include "singleton.h"

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

/*
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
		ImGui::Text("- Press U to lock or unlock the cursor!");
		ImGui::Text("- You can open the options by unlocking \n the cursor, and clicking File (top-left)!");
		ImGui::Text("\n");

		// Set the text color to red
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

		ImGui::Text("Player Score : %d", LabEngine::getInstance().ourGameData.score);

		ImGui::PopStyleColor();

		// Set the text color to green
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));

		ImGui::Text("\n\nTime Left : %d", timeMgr.getTimer("gameEndTimer")->getSecondsRemaining());

		ImGui::PopStyleColor();

		// Set the text color to light blue
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.8f, 0.9f, 1.0f));

		ImGui::Text("\nFPS : %d", (int)LabEngine::getInstance().m_window->getFPS());

		ImGui::PopStyleColor();




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
*/

void EngGUI::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	setupUserInterfaceStyle();

	if (show_demo_window)
	{
		demoWindow();
	}

	imageWindow();
	callPauseMenu();
}

void EngGUI::setupUserInterfaceStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.15f, 1.00f); // Dark grey
	style.Colors[ImGuiCol_Button] = ImVec4(0.61f, 0.35f, 0.71f, 1.00f); // Purple
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.68f, 0.40f, 0.78f, 1.00f); // Lighter purple
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.84f, 0.43f, 0.99f, 1.00f); // Even lighter purple
}

void EngGUI::demoWindow()
{
	ImGui::SetNextWindowSize(ImVec2(300, 300));
	ImGui::Begin("Welcome to our Demo!");
	ImGui::Spacing();
	ImGui::Text("- You can open the options by pressing \n the M key!");
	// Set the text color to red
	ImGui::Spacing();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	ImGui::Text("Player Score : %d", LabEngine::getInstance().ourGameData.score);
	ImGui::PopStyleColor();
	// Set the text color to green
	ImGui::Spacing();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
	ImGui::Text("\n\nTime Left : %d", timeMgr.getTimer("gameEndTimer")->getSecondsRemaining());
	ImGui::PopStyleColor();
	// Set the text color to light blue
	ImGui::Spacing();
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.8f, 0.9f, 1.0f));
	ImGui::Text("\nFPS : %d", (int)LabEngine::getInstance().m_window->getFPS());
	ImGui::PopStyleColor();
	ImGui::End();
}

void EngGUI::imageWindow()
{
	if (show_image) {

		glfwSetInputMode(m_PixelsGLFWWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		ImVec2 image_size(1000, 700);


		ImGui::Begin("Image Display");
		ImGui::Image((void*)(intptr_t)image_texture_id, image_size, ImVec2(0, 1), ImVec2(1, 0));

		if (ImGui::IsItemClicked())
		{
			glfwSetWindowShouldClose(m_PixelsGLFWWindow, true);
		}
		ImGui::End();

	}
	

}

void EngGUI::callPauseMenu()
{
	/*
	try
	{
		bool showPauseMenu = true;
		int state = glfwGetKey(LabEngine::getInstance().m_window->m_PixelsGLFWWindow, GLFW_KEY_P);

		if (state == GLFW_PRESS)
		{
			showPauseMenu = !showPauseMenu;
		}

		if (showPauseMenu)
		{
			generatePauseMenu(showPauseMenu);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	*/

	//------------
	if (showPauseMenu)
	{
		generatePauseMenu(showPauseMenu);
		//generatePauseMenu(showPauseMenu);
	}
}

void EngGUI::generatePauseMenu(bool men)
{
	bool show_menu = true;
	ImGui::SetNextWindowSize(ImVec2(400, 200));
	show_menu = !show_menu;
	int windowWidth, windowHeight;
	glfwGetWindowSize(LabEngine::getInstance().m_window->m_PixelsGLFWWindow, &windowWidth, &windowHeight);

	// Center the window on the screen
	ImGui::SetNextWindowPos(ImVec2(windowWidth * 0.5f - 150.0f, windowHeight * 0.5f - 100.0f));
	//ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	if (!ImGui::Begin("Main Menu", &showPauseMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::End();
		return;
	}


	// Layout and Style
	ImGui::Columns(2, "mixed");
	ImGui::SetColumnWidth(-1, 150);
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Game Options");
	ImGui::NextColumn();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Support");
	ImGui::NextColumn();


	// Game Options
	if (ImGui::Button("Movement Controls")) { ImGui::OpenPopup("Movement Controls"); }
	if (ImGui::Button("Camera Controls")) { ImGui::OpenPopup("Camera Controls"); }
	if (ImGui::Button("Other Controls")) { ImGui::OpenPopup("Other Controls"); }
	if (ImGui::Button("Save")) { ImGui::OpenPopup("Save Game"); }
	if (ImGui::Button("Load")) { ImGui::OpenPopup("Load Game"); }
	if (ImGui::Button("Quit")) { ImGui::OpenPopup("Quit Confirmation"); }




	ImGui::NextColumn();

	// Support
	if (ImGui::Button("Customer Support")) { ImGui::OpenPopup("Customer Support"); }

	ImGui::Columns(1);
	ImGui::Separator();
	if (ImGui::Button("Resume", ImVec2(-1, 0))) { show_menu = false; 
	showPauseMenu = false;
	LabEngine::getInstance().m_window->toggleMouse();
	LabEngine::getInstance().m_camera->toggleMouseMovement();
	}

	// Call your functions here
	
	generateMovementControls();
	generateCameraControls();
	generateOtherControls();
	generateCustomerSupport();
	generateSaveConfirmation();
	generateLoadConfirmation();
	generateQuitConfirmation();
	

	ImGui::End();
}


void EngGUI::generateQuitConfirmation()
{
	if (ImGui::BeginPopupModal("Quit Confirmation", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Are you sure you want to quit the game?");

		if (ImGui::Button("Yes", ImVec2(120, 0)))
		{
			LabEngine::getInstance().m_window->shouldClose();
			ImGui::CloseCurrentPopup();
			exit(0);  // Call exit(0) here, after the user confirms they want to quit
		}

		ImGui::SameLine();

		if (ImGui::Button("No", ImVec2(120, 0)))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void EngGUI::generateLoadConfirmation()
{
	if (ImGui::BeginPopupModal("Load Game", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Are you sure you want to load ? ");

		if (ImGui::Button("Yes", ImVec2(200, 100)))
		{
			load_game();
		}
		ImGui::SameLine();

		if (ImGui::Button("No", ImVec2(200, 100)))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void EngGUI::generateSaveConfirmation()
{
	if (ImGui::BeginPopupModal("Save Game", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Are you sure you want to save the game ?");

		if (ImGui::Button("Yes", ImVec2(200, 100)))
		{
			save_game();
		}
		ImGui::SameLine();

		if (ImGui::Button("No", ImVec2(200, 100)))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}


void EngGUI::generateOtherControls()
{
	if (ImGui::BeginPopupModal("Other Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("K     : Trigger wireframe mode!");
		ImGui::Spacing();
		ImGui::Text("X     : Quit Demo");
		ImGui::Spacing();
		ImGui::Text("U     : Unlock mouse!");
		ImGui::Spacing();
		ImGui::Text("M     : Show / Hide Frames per second");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Space : Throw boxes at NPCS");

		backButton();
	}
}


void EngGUI::generateCameraControls()
{
	if (ImGui::BeginPopupModal("Camera Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Mouse up    : look up");
		ImGui::Text("Mouse down  : look down");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Mouse left  : look left");
		ImGui::Text("Mouse right : look right");


		backButton();
	}
}

void EngGUI::generateCustomerSupport()
{
	if (ImGui::BeginPopupModal("Customer Support", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Contact our customer support for assistance:");
		ImGui::Spacing();
		ImGui::Text("Name : William Halling Howard");
		ImGui::Spacing();
		ImGui::Text("Email: 32233703@studentmurdoch.edu.au");
		ImGui::Spacing();
		ImGui::Text("Student Number : 32233703");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Name  : Jason Botterill");
		ImGui::Spacing();
		ImGui::Text("Email : jasonbotterill@hotmail.com");
		ImGui::Spacing();
		ImGui::Text("Student Number : 33974906");

		//ImGui::EndPopup();
		backButton();
	}
}

void EngGUI::generateMovementControls()
{
	if (ImGui::BeginPopupModal("Movement Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("W: Forward");
		ImGui::Spacing();
		ImGui::Text("S: Backward");
		ImGui::Spacing();
		ImGui::Text("A: Left");
		ImGui::Spacing();
		ImGui::Text("D: Right");
		ImGui::Spacing();
		ImGui::Text("F: Fly Around Terrain!");
		


		backButton();
	}
}

void EngGUI::backButton()
{

	if ( ImGui::Button("Close", ImVec2(120, 0)) )
	{
		ImGui::CloseCurrentPopup();
	}
	ImGui::EndPopup();

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