#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SoundManager.h"

enum class GameStateID { Gameplay, MainMenu, PauseMenu, Settings, GameOver, GameWin, Loading, Retry, Back, Exit};

class GameState {
public:
    GameState() = default;
    virtual ~GameState() = default;
    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void exit() = 0;
    bool isStateChangeRequested() const;
    GameStateID getNextStateID() const;
    void requestStateChange(GameStateID nextStateID);
    void clearStateChangeRequest();
    void setLoadLevel();
    bool isLoadLevel() const;

private:
    bool m_stateChangeRequested = false;
    bool m_loadLevel = false;
    GameStateID m_nextStateID = GameStateID::MainMenu;
};