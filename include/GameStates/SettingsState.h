#pragma once

#include "GameState.h"
#include <vector>
#include "TextureManager.h"
#include "SoundManager.h"
#include "Config.h"

class SettingsState : public GameState {
public:
    SettingsState();
    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) override;
    virtual void update(float) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void pause() override {};
    virtual void resume() override {};
    virtual void exit() override {};

private:
    sf::Sprite m_background;
    sf::Sprite m_soundfx;
    sf::Sprite m_music;
    sf::Sprite m_back;
    sf::Sprite m_upSoundFx;
    sf::Sprite m_downSoundFx;
    sf::Sprite m_upMusic;
    sf::Sprite m_downMusic;
    sf::Sound m_click;
    
    void setVolume();
};