#pragma once

#include "GameState.h"

class GameOverState : public GameState {
public:
    GameOverState();
    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) override;
    virtual void update(float) override {};
    virtual void render(sf::RenderWindow& window) override;
    virtual void pause() override {};
    virtual void resume() override {};
    virtual void exit() override {};

private:
    sf::Sprite m_backGround;
    sf::Sprite m_retry;
    sf::Sprite m_exit;
    sf::Sound m_gameOverSound;
    sf::Sound m_click;

};