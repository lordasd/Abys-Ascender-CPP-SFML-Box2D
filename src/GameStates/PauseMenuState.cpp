#include "PauseMenuState.h"

PauseMenuState::PauseMenuState()
    :   m_click(SoundManager::instance().getClick()),
        m_backGround(TextureManager::instance().getPauseMenu())
{
    m_buttons.emplace_back(TextureManager::instance().getResume());
    m_buttons.back().setPosition(WINDOW_WIDTH / 2.f - 175.f, 230.f);
    m_buttons.emplace_back(TextureManager::instance().getMenuButton(2));
    m_buttons.back().setPosition(WINDOW_WIDTH / 2.f - 175.f, 400.f);
    m_buttons.emplace_back(TextureManager::instance().getMenuButton(4));
    m_buttons.back().setPosition(WINDOW_WIDTH / 2.f - 175.f, 570.f);
}

void PauseMenuState::handleInput(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        // Click button sound
        for (int i = 0; i < static_cast<int>(Buttons::Amount); ++i)
        {
            if (i == static_cast<int>(Buttons::Resume) &&
                m_buttons[i].getGlobalBounds().contains(mousePos))
            {
                m_click.play();
                requestStateChange(GameStateID::Exit);
                break;
            }
            else if (i == static_cast<int>(Buttons::Settings) &&
                m_buttons[i].getGlobalBounds().contains(mousePos))
            {
                m_click.play();
                requestStateChange(GameStateID::Settings); // Request state change to SettingsState
                break; // No need to check other buttons if settings button is clicked
            }
            else if (i == static_cast<int>(Buttons::Exit) &&
                m_buttons[i].getGlobalBounds().contains(mousePos))
            {
                m_click.play();
                requestStateChange(GameStateID::Back);
                break;
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStateChange(GameStateID::Exit);
}

void PauseMenuState::update(float)
{
    m_click.setVolume(SoundManager::instance().getSoundFxVol());
}

void PauseMenuState::render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());

    window.draw(m_backGround);
    for (const auto& button : m_buttons)
        window.draw(button);
}