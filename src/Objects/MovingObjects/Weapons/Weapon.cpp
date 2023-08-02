#include "Weapon.h"

Weapon::Weapon(const sf::Sprite& sprite, const sf::Vector2f& position, float velocity, float lifeTime)
	:	MovingObject(sprite, position, velocity), m_lifeTime(lifeTime) {}

Weapon::Weapon(const sf::Vector2f& position, float velocity, float lifeTime)
	:	MovingObject(position, velocity), m_lifeTime(lifeTime) {}

void Weapon::update(float deltaTime)
{
    // Get the current velocity
    b2Vec2 currentVelocity = getBody()->GetLinearVelocity();

    m_elapsedTime += deltaTime;
    if (m_elapsedTime > m_lifeTime) // Destroy object
    {
        m_hit = true;
        return;
    }

    if (getDirection() == Direction::Right)
    {
        // Shoot the weapon right
        b2Vec2 force(getVelocity(), 0.0f); // Set force
        if (currentVelocity.x < getVelocity()) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }
    else if (getDirection() == Direction::Left)
    {
        // Shoot the weapon left
        b2Vec2 force(-getVelocity(), 0.0f); // Set force
        if (currentVelocity.x > -getVelocity()) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }

    // Set position and origin for the sprite
    m_sprite.setPosition((getBody()->GetPosition().x * PPM),
         WINDOW_HEIGHT - (getBody()->GetPosition().y * PPM));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f,
                       m_sprite.getLocalBounds().height / 2.f);
}

void Weapon::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

bool Weapon::isHit() const
{
    return m_hit;
}

void Weapon::setHit()
{
    m_hit = true;
}
