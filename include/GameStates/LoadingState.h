#pragma once

#include "GameState.h"
#include <fstream>

class LoadingState : public GameState {
public:
	LoadingState();
	virtual void handleInput(const sf::Event&, const sf::Vector2f&) override {};
	virtual void update(float deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;
	virtual void pause() override {};
	virtual void resume() override {};
	virtual void exit() override {};

private:
	sf::Sprite m_background;
	float m_elapsedTime{};
};