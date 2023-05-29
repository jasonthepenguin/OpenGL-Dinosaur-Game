#include "PausedGameState.h"


void handlePlayerInput() override;
void Update() override;
void Generate() override;

std::map<std::string, std::shared_ptr<PauseMenu_Commands>> commandMap;

PausedGameState::PausedGameState(std::shared_ptr<Window> window, std::shared_ptr<Keyboard_Input> keyboardInput, std::shared_ptr<Mouse_Input> mouseInput, std::shared_ptr<EngGUI> gui) :
    m_window(window),
    m_keyboardInput(keyboardInput),
    m_mouseInput(mouseInput),
    m_DisplayOptions(gui)
{
    commandMap["resume"] = std::make_shared<ResumeCommand>();
    commandMap["save"] = std::make_shared<SaveCommand>();
}


PausedGameState::~PausedGameState(){}


void PausedGameState::handlePlayerInput()
{
    //sf::Event event;

    //while (window.pollEvent(event)) 
    {
        
    }
}

void PausedGameState::update()
{
    m_DisplayOptions->beginFrame();
    if (ImGui::Begin("Pause Menu"))
    {
        if (ImGui::Button("Resume Game"))
        {

        }
    }
}

void PausedGameState::generate()
{
    //window.clear();
    // Render the paused menu
    //window.display();
}


/************

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

class EmailGenerator {
public:
    static void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) {
        // Logic for sending the email goes here
        std::cout << "Sending email to: " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Body: " << body << std::endl;
    }
};


class CustomerSupportCommandWithEmail : public CustomerSupportCommand {
private:
    std::string m_Subject;
    std::string m_Body;

public:
    CustomerSupportCommandWithEmail() : m_Subject(""), m_Body("") {}

    void setSubject(const std::string& subject) {
        m_Subject = subject;
    }

    void setBody(const std::string& body) {
        m_Body = body;
    }

    void generate() override {
        DisplaySupportInfo();

        // Prompt user for subject and body
        ImGui::InputText("Subject", &m_Subject);
        ImGui::InputTextMultiline("Body", &m_Body);

        if (ImGui::Button("Send Email")) {
            // Generate and send the email
            EmailGenerator::sendEmail(m_ContactEmail, m_Subject, m_Body);
        }
    }
};

class CustomerSupportCommand {
private:
    struct Availability {
        std::string day;
        std::string time;
    };

protected:
    std::string m_Details;
    std::string m_ContactName;
    std::string m_ContactEmail;
    std::vector<Availability> m_Availability;

public:
    CustomerSupportCommand() :
        m_Details("Customer Support"),
        m_ContactName("John Doe"),
        m_ContactEmail("john.doe@example.com") {}

    void DisplaySupportInfo() {
        ImGui::Begin("Customer Support");
        ImGui::Text(("Details: " + m_Details).c_str());
        ImGui::Text(("Contact Name: " + m_ContactName).c_str());
        ImGui::Text(("Contact Email: " + m_ContactEmail).c_str());

        ImGui::Text("Availability:");
        for (const auto& availability : m_Availability) {
            ImGui::Text((availability.day + ": " + availability.time).c_str());
        }

        ImGui::End();
    }

    virtual void generate() {
        DisplaySupportInfo();
    }
};
