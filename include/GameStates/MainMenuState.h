#pragma once

#include "GameState.h"
#include "MainMenuButton.h"
#include "Config.h"
#include <fstream>

enum class MenuState { Main, Help };

class MainMenuState : public GameState {
public:
    MainMenuState();
    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) override;
    virtual void update(float deltaTime) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void exit() override;

private:
    MenuState m_state = MenuState::Main;
    std::vector<MainMenuButton> m_buttons;
    sf::Sprite m_menuBackground;
    sf::Sprite m_helpMenu;
    sf::Sprite m_helpMenu2;
    float m_zoomLevel = 1.f;
    sf::Music* m_mainMenuMusic;
    sf::Sound m_click;

    sf::Sprite m_back;
    size_t m_page = 1;
    sf::Sprite m_arrow_right;
    sf::Sprite m_arrow_left;

    void resetSaveFile() const;
};