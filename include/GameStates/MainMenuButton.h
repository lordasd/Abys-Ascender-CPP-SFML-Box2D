#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

enum class ButtonType { NewGame, Continue, Settings, Help, Exit, None};

class MainMenuButton {
public:
	MainMenuButton(size_t buttonNum, const sf::Vector2f& buttonPos);
	void handleInput(const sf::Vector2f& mousePos);
	void update(float);
	void render(sf::RenderWindow& window) const;
	ButtonType getType() const;
	bool isClicked() const;

private:
	sf::Sprite m_sprite;
	ButtonType m_type = ButtonType::None;
	bool m_clicked = false;
};