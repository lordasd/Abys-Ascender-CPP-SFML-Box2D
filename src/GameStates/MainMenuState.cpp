#include "MainMenuState.h"

MainMenuState::MainMenuState()
    :   m_menuBackground(TextureManager::instance().getMainMenu()),
        m_mainMenuMusic(SoundManager::instance().getMainMenuMusic()),
        m_helpMenu(TextureManager::instance().getHelpMenu()),
        m_helpMenu2(TextureManager::instance().getHelpMenu2()),
        m_arrow_left(TextureManager::instance().getArrowLeft()),
        m_arrow_right(TextureManager::instance().getArrowRight()),
        m_click(SoundManager::instance().getClick()),
        m_back(TextureManager::instance().getBack())
{
    m_buttons.reserve(BUTTONS_AMOUNT);
    sf::Vector2f buttonPos{ WINDOW_WIDTH / 2.f - 175.f , 155.f };
    for (size_t buttonNum{}; buttonNum < BUTTONS_AMOUNT; ++buttonNum, buttonPos.y += 105.f)
        m_buttons.emplace_back(MainMenuButton(buttonNum, buttonPos));

    // Set help menu buttons position
    m_back.setPosition(WINDOW_WIDTH / 2.f - 170.f, 640.f);
    m_arrow_left.setPosition(20.f, WINDOW_HEIGHT - WINDOW_HEIGHT / 2);
    m_arrow_right.setPosition(WINDOW_WIDTH - 115.f, WINDOW_HEIGHT - WINDOW_HEIGHT / 2);

    // Turn music on
    m_mainMenuMusic->setLoop(true);
    m_mainMenuMusic->play();
}

void MainMenuState::handleInput(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (m_state == MenuState::Main)
        {
            for (auto& button : m_buttons)
            {
                button.handleInput(mousePos);

                if (button.getType() == ButtonType::NewGame && button.isClicked())
                {
                    m_click.play();
                    resetSaveFile();
                    requestStateChange(GameStateID::Gameplay); // Request state change to SettingsState
                    break; // No need to check other buttons if settings button is clicked
                }
                else if (button.getType() == ButtonType::Continue && button.isClicked())
                {
                    m_click.play();
                    setLoadLevel(); // Set load level true;
                    requestStateChange(GameStateID::Gameplay);
                    break;
                }
                else if (button.getType() == ButtonType::Settings && button.isClicked())
                {
                    m_click.play();
                    requestStateChange(GameStateID::Settings);
                    break;
                }
                if (button.getType() == ButtonType::Help && button.isClicked())
                {
                    m_click.play();
                    m_state = MenuState::Help;
                }
                else if (button.getType() == ButtonType::Exit && button.isClicked())
                {
                    m_click.play();
                    requestStateChange(GameStateID::Exit);
                    break;
                }
            }
        }
        else if (m_state == MenuState::Help) // Help pages
        {
            if (m_page == 1 && m_arrow_right.getGlobalBounds().contains(mousePos))
            {
                m_click.play();
                m_page = 2;
            }
            else if (m_page == 2 && m_arrow_left.getGlobalBounds().contains(mousePos))
            {
                m_click.play();
                m_page = 1;
            }
            else if (m_page == 1 && m_back.getGlobalBounds().contains(mousePos))
            {
                m_click.play();
                m_state = MenuState::Main;
            }
        }
    }
}

void MainMenuState::update(float deltaTime)
{
    m_click.setVolume(SoundManager::instance().getSoundFxVol());

    for (auto& button : m_buttons)
        button.update(deltaTime);
}

void MainMenuState::render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());

    if (m_state == MenuState::Main)
    {
        window.draw(m_menuBackground);
        for (const auto& button : m_buttons)
            button.render(window);
    }
    else
    {
        if (m_page == 1)
        {
            window.draw(m_helpMenu);
            window.draw(m_arrow_right);
            window.draw(m_back);
        }
        else if (m_page == 2)
        {
            window.draw(m_helpMenu2);
            window.draw(m_arrow_left);
        }
    }
}

void MainMenuState::pause()
{
    if(getNextStateID() != GameStateID::Settings)
        m_mainMenuMusic->stop();
}

void MainMenuState::resume()
{
    m_click.setVolume(SoundManager::instance().getSoundFxVol());
    m_mainMenuMusic->play();
}

void MainMenuState::exit()
{
    m_mainMenuMusic->stop();
}

void MainMenuState::resetSaveFile() const
{
    std::ofstream file(SAVEFILE);

    if (!file.is_open())
        throw std::runtime_error("Failed to open file");

    // Write new content to the file
    file << LEVEL1; // Insert first level

    // Close the file
    file.close();
}
