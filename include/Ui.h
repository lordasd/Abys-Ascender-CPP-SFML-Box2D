#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"
#include "SoundManager.h"

class Ui {
public:
	Ui(const sf::View& view);
	void update(float deltaTime, size_t healthAmount);
	void render(sf::RenderWindow& window);
	void setLevel(size_t level);

private:
	sf::Sprite m_hp;
	sf::Sprite m_heart;
	sf::Sprite m_emptyHeart;
	std::vector<sf::Sprite> m_health;
	size_t m_hpAmount{ 4 };
	sf::Font m_font;
	sf::Text m_level;
	const sf::View& m_view;

	void setSpritePositions(sf::RenderWindow& window);
};