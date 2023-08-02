#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include <box2d/box2d.h>
#include <iostream>
#include <math.h>
#include "TextureManager.h"
#include "SoundManager.h"

class GameObject {
public:
	GameObject(const sf::Texture& texture, const sf::Vector2f& position);
	GameObject(const sf::Sprite& texture, const sf::Vector2f& position);
	GameObject(const sf::Sprite& texture);
	GameObject(const sf::Vector2f& position);
	virtual ~GameObject() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) const = 0;
	const sf::Vector2f& getPosition() const;

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};