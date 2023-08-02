#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position)
	:  m_sprite(texture)
{
	m_sprite.setPosition(position);
	m_position = position;
}

GameObject::GameObject(const sf::Sprite& texture, const sf::Vector2f& position)
	: m_sprite(texture)
{
	m_sprite.setPosition(position);
	m_position = position;
}

GameObject::GameObject(const sf::Sprite& texture)
	: m_sprite(texture){}

GameObject::GameObject(const sf::Vector2f& position)
	: m_position(position) {}

const sf::Vector2f& GameObject::getPosition() const
{
	return m_sprite.getPosition();
}
