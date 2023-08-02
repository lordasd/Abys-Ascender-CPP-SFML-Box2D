#include "Drop.h"

Drop::Drop(const sf::Sprite& sprite, const sf::Vector2f& position, float interval, float velocity, b2World* world)
    :   MovingObject(sprite, position, velocity), m_interval(interval)
{
    // Create Box2D body and fixtures for the moving object
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(position.x / PPM, position.y / PPM);
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(DROP_WIDTH / 2.f / PPM,
                       DROP_HEIGHT / 2.f / PPM);

    // Create the fixture definition for the body
    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.density = 0.3f; // Set the density of the body
    bodyFixtureDef.friction = 1.f; // Set the friction of the body
    bodyFixtureDef.restitution = 0.f;
    bodyFixtureDef.isSensor = true; // Disable contact
    bodyFixtureDef.shape = &bodyShape;

    setBody(world->CreateBody(&bodyDef));
    // Create the fixture for the body in the Box2D body
    getBody()->CreateFixture(&bodyFixtureDef);

    setDirection(Direction::Down);
}

void Drop::update(float deltaTime)
{
    // Get the current velocity
    b2Vec2 currentVelocity = getBody()->GetLinearVelocity();

    m_elapsedTime += deltaTime;

    // Check if time to change direction
    if (m_elapsedTime > m_interval)
    {
        if (getDirection() == Direction::Down || getDirection() == Direction::Up)
            setDirection(getDirection() == Direction::Down ? Direction::Up : Direction::Down);
        m_elapsedTime = 0.f;
    }

    if (getDirection() == Direction::Down)
    {
        // Move the drop downwards
        b2Vec2 force(0.0f, -getVelocity());
        if (currentVelocity.x > -DROP_VELOCITY) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }
    else if (getDirection() == Direction::Up)
    {
        // Move the drop upwards
        b2Vec2 force(0.0f, getVelocity()); // Set force
        if (currentVelocity.x < DROP_VELOCITY) // Check max speed in the x direction
            getBody()->SetLinearVelocity(force);
    }

    // Set current position for the sprite after drops movement
    m_sprite.setPosition(getBody()->GetPosition().x * PPM,
        WINDOW_HEIGHT - (getBody()->GetPosition().y * PPM));
    m_sprite.setOrigin(DROP_WIDTH / 2.f, DROP_HEIGHT / 2.f);
}

void Drop::remove()
{
    m_remove = true;
}

bool Drop::needRemove() const
{
    return m_remove;
}
