#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(const sf::Texture& texture, const sf::Vector2f& position, float interval, float velocity)
    : MovingObject(texture, position, velocity), m_interval(interval) {}

void MovingPlatform::update(float deltaTime)
{
    // Get the current velocity
    b2Vec2 currentVelocity = getBody()->GetLinearVelocity();

    m_elapsedTime += deltaTime;

    if (m_elapsedTime > m_interval)
    {
        // Elevator or Side platform
        if (getDirection() == Direction::Left || getDirection() == Direction::Right)
            setDirection(getDirection() == Direction::Left ? Direction::Right : Direction::Left);
        else if (getDirection() == Direction::Down || getDirection() == Direction::Up)
            setDirection(getDirection() == Direction::Down ? Direction::Up : Direction::Down);

        m_elapsedTime = 0.f;
    }

    if (getDirection() == Direction::Down)
    {
        // Move the platform downwards
        b2Vec2 force(0.0f, -getVelocity());
        if (currentVelocity.x > -PLATFORM_MAX_VELOCITY) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }
    else if (getDirection() == Direction::Up)
    {
        // Move the platform upwards
        b2Vec2 force(0.0f, getVelocity()); // Set force
        if (currentVelocity.x < PLATFORM_MAX_VELOCITY) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }
    else if (getDirection() == Direction::Right)
    {
        // Move the platform upwards
        b2Vec2 force(getVelocity(), 0.0f); // Set force
        if (currentVelocity.x < PLATFORM_MAX_VELOCITY) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }
    else if (getDirection() == Direction::Left)
    {
        // Move the platform to the left
        b2Vec2 force(-getVelocity(), 0.0f); // Set force
        if (currentVelocity.x > -PLATFORM_MAX_VELOCITY) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }

    // Set current position for the sprite after platform movement
    m_sprite.setPosition(((m_chainShape.m_vertices->x + getBody()->GetPosition().x) * PPM) - 3.f,
         WINDOW_HEIGHT - ((m_chainShape.m_vertices->y + getBody()->GetPosition().y) * PPM));
}

const b2Vec2* MovingPlatform::getVertices() const
{
    return m_chainShape.m_vertices;
}

int32 MovingPlatform::getVerticesAmount() const
{
    return m_chainShape.m_count;
}
