#pragma once

#include "GameState.h"

class GameWinState : public GameState {
public:
    GameWinState();
    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) override;
    virtual void update(float) override {};
    virtual void render(sf::RenderWindow& window) override;
    virtual void pause() override {};
    virtual void resume() override {};
    virtual void exit() override {};

private:
    sf::Sprite m_backGround;
    sf::Sprite m_exit;
    sf::Sound m_gameWinSound;
    sf::Sound m_click;

};