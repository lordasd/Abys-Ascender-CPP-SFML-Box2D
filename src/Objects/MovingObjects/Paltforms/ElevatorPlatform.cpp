#include "ElevatorPlatform.h"

ElevatorPlatform::ElevatorPlatform(const sf::Texture& texture, const sf::Vector2f& position, const Direction& direction, float interval, float velocity, b2World* world)
    :   MovingPlatform(texture, position, interval, velocity)
{
    // Create Box2D body and fixtures for the moving object
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(0, 0);
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    setBody(world->CreateBody(&bodyDef));

    float width = m_sprite.getGlobalBounds().width;
    float height = m_sprite.getGlobalBounds().height;

    // Create the ground
    b2Vec2 vs[4];
    vs[0].Set(position.x / PPM, position.y / PPM);
    vs[1].Set(position.x / PPM, (position.y - height) / PPM);
    vs[2].Set((position.x + width - 5.f) / PPM, (position.y - height) / PPM);
    vs[3].Set((position.x + width - 5.f) / PPM, position.y / PPM);
    m_chainShape.CreateLoop(vs, 4);
    getBody()->CreateFixture(&m_chainShape, 0.f);

    setDirection(direction); // Initial direction of the platform
}
