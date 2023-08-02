#include "FinishLine.h"

FinishLine::FinishLine(const sf::Vector2f& position, b2World* world)
	: StaticObject(position, true)
{
    // Create the Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x / PPM, position.y / PPM);
    bodyDef.type = b2_staticBody;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    // Create the Box2D fixture definition for the shape of the object
    b2PolygonShape shape;
    shape.SetAsBox(TILE_SIZE / 2.f / PPM, TILE_SIZE / 2.f / PPM);

    // Create the Box2D body using the body definition
    setBody(world->CreateBody(&bodyDef));

    // Create the Box2D fixture using the shape and attach it to the body
    getBody()->CreateFixture(&shape, 0.0f);
}