#pragma once

#include "GameState.h"

enum class Buttons { Resume, Settings, Exit, Amount };

class PauseMenuState : public GameState {
public:
    PauseMenuState();
    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) override;
    virtual void update(float deltaTime) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void pause() override {};
    virtual void resume() override {};
    virtual void exit() override {};

private:
    std::vector<sf::Sprite> m_buttons;
    sf::Sound m_click;
    sf::Sprite m_backGround;
};