#include "MovingObject.h"

MovingObject::MovingObject(const sf::Sprite& sprite, float velocity, b2World* world)
    :   GameObject(sprite), m_velocity(velocity), m_body(nullptr), m_world(world) {}

MovingObject::MovingObject(const sf::Sprite& sprite, const sf::Vector2f position, float velocity)
    :   GameObject(sprite, position), m_velocity(velocity), m_body(nullptr), m_world(nullptr) {}

MovingObject::MovingObject(const sf::Texture& texture, const sf::Vector2f& position, float velocity, b2World* world)
    :   GameObject(texture, position), m_velocity(velocity), m_body(nullptr), m_world(world) {}

MovingObject::MovingObject(const sf::Texture& texture, const sf::Vector2f& position, float velocity)
    :   GameObject(texture, position), m_velocity(velocity), m_body(nullptr), m_world(nullptr) {}

MovingObject::MovingObject(const sf::Vector2f& position, float velocity)
    :   GameObject(position), m_velocity(velocity), m_body(nullptr), m_world(nullptr) {}

void MovingObject::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

float MovingObject::getVelocity() const
{
    return m_velocity;
}

void MovingObject::setVelocity(float velocity)
{
    m_velocity = velocity;
}

const b2Vec2& MovingObject::getDampingFactor() const
{
    return m_dampingFactor;
}

Direction MovingObject::getDirection() const
{
    return m_currDirection;
}

void MovingObject::setDirection(const Direction& direction)
{
    m_currDirection = direction;
}

b2Body* MovingObject::getBody() const
{
    return m_body;
}

size_t MovingObject::getCollisions() const
{
    return m_collisions;
}

void MovingObject::addToCollision(int x)
{
    m_collisions += x;
}

size_t MovingObject::getFloorsTouching() const
{
    return m_floorsTouching;
}

void MovingObject::addFloorsTouching(int x)
{
    m_floorsTouching += x;
}

b2World* MovingObject::getWorld() const
{
    return m_world;
}

void MovingObject::setBody(b2Body* body)
{
    m_body = body;
}
