#include "Arrow.h"

Arrow::Arrow(const sf::Sprite& sprite, const Direction& direction, const sf::Vector2f& position, b2World* world)
    :   Weapon(sprite, position, ARROW_VELOCITY, ARROW_LIFETIME)
{
    // Create Box2D body for the projectile
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    sf::Vector2f newPos{position};
    if (direction == Direction::Left)
    {
        newPos.x -= 25.f;
        m_sprite.setScale(-0.5f, 0.5f);
    }
    else
        newPos.x += 25.f;
    newPos.y += 7.f;

    bodyDef.position.Set(newPos.x / PPM, newPos.y / PPM);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.bullet = true;
    setBody(world->CreateBody(&bodyDef));
    setDirection(direction);

    // Create Box2D shape for the sword
    b2PolygonShape shape;
    shape.SetAsBox(10.f / PPM, 5.f / PPM);

    // Define the fixture for the sword
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.1f;  // Adjust density as needed
    fixtureDef.isSensor = true; // Disable contact

    // Attach the fixture to the body
    getBody()->CreateFixture(&fixtureDef);
}