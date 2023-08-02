#include "Sword.h"

Sword::Sword(const Direction& direction, const sf::Vector2f& position, b2World* world)
    :   Weapon(position, SWORD_VELOCITY, SWORD_LIFETIME)
{
    // Create Box2D body for the projectile
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    sf::Vector2f newPos{position};
    if (direction == Direction::Left)
        newPos.x -= 22.f;
    else
        newPos.x += 22.f;
    bodyDef.position.Set(newPos.x / PPM, newPos.y / PPM);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bodyDef.bullet = true;
    setBody(world->CreateBody(&bodyDef));
    setDirection(direction);

    // Create Box2D shape for the sword
    b2PolygonShape shape;
    shape.SetAsBox((TILE_SIZE - 5.f) / 2.f / PPM , TILE_SIZE  / 2.f / PPM);

    // Define the fixture for the sword
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;  // Adjust density as needed
    fixtureDef.friction = 0.2f; // Adjust friction as needed
    fixtureDef.isSensor = true; // Disable contact

    // Attach the fixture to the body
    getBody()->CreateFixture(&fixtureDef);
}