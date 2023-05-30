#include "GamePaused_State.h"



std::map<std::string, std::shared_ptr<Menu_Commands>> commandMap;

GamePaused_State::GamePaused_State(std::shared_ptr<Window> window, std::shared_ptr<Keyboard_Input> keyboardInput, std::shared_ptr<Mouse_Input> mouseInput, std::shared_ptr<EngGUI> gui) :
    m_window(window),
    m_keyboardInput(keyboardInput),
    m_mouseInput(mouseInput),
    m_DisplayOptions(gui)
{

    commandMap["Resume Game"] = std::make_shared<ResumeCommand>();
    commandMap["Save Game"]   = std::make_shared<SaveCommand>();
    commandMap["Load Game"]   = std::make_shared<Load_Command>();
}


GamePaused_State::~GamePaused_State(){}


void GamePaused_State::handlePlayerInput()
{
    //sf::Event event;

    //while (window.pollEvent(event)) 
    {
        
    }
}

void GamePaused_State::update()
{
    m_DisplayOptions->beginFrame();
    if (ImGui::Begin("Pause Menu"))
    {
        if (ImGui::Button("Resume Game"))
        {

        }
    }
}

void GamePaused_State::generate()
{
    //window.clear();
    // Render the paused menu
    //window.display();
}


/************
void handlePlayerInput();
void Update() override;
void Generate() override;

GamePausedState::GamePausedState(QWidget* parent) : QMainWindow(parent)
{
    // Create the SFML window
    sfmlWindow.create(sf::VideoMode(800, 600), "Game Window");

    // Set up the timer to update and draw at regular intervals
    connect(&timer, &QTimer::timeout, this, &GamePausedState::update);
    connect(&timer, &QTimer::timeout, this, &GamePausedState::draw);
    timer.start(16); // 60 FPS (16ms per frame)

    // Other initialization code for menu items, buttons, etc.
}

GamePausedState::~GamePausedState() {
    // Clean up any resources
}

void GamePausedState::handleInput() {
    sf::Event event;
    while (sfmlWindow.pollEvent(event)) {
        // Handle user input events
        // Update menu items or buttons based on user input
    }
}

void GamePausedState::update() 
{
    // Update the paused menu state
}

void GamePausedState::draw() 
{
    sfmlWindow.clear();
    sfmlWindow.display();

}
*****/