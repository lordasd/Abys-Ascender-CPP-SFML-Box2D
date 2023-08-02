#include "ChainedObject.h"
#include "Player.h"

ChainedObject::ChainedObject(const sf::Vector2f& position, b2World* world)
    : StaticObject(position, true)
{
    // Create the Box2D body definition
    b2BodyDef bodyDef;
    bodyDef.position.Set(0, 0);
    bodyDef.type = b2_staticBody;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    // Create the Box2D body using the body definition
    setBody(world->CreateBody(&bodyDef));
}

void ChainedObject::update(float)
{

}

void ChainedObject::createChain(const sf::Vector2f& startPos, const sf::Vector2f& endPos, const Shape& shape)
{
    if (shape == Shape::Square)
    {
        b2Vec2 vs[4];
        vs[0].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetY) / PPM);
        vs[1].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetY) / PPM);
        vs[2].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetYDown) / PPM);
        vs[3].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetYDown) / PPM);
        m_chainShape.CreateLoop(vs, 4);
        getBody()->CreateFixture(&m_chainShape, 0.f);
    }
    else if (shape == Shape::Tri0)
    {
        // Point down right
        b2Vec2 vs[3];
        vs[0].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetY) / PPM);
        vs[1].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetYDown) / PPM);
        vs[2].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetYDown) / PPM);
        m_chainShape.CreateLoop(vs, 3);
        getBody()->CreateFixture(&m_chainShape, 0.f);
    }
    else if (shape == Shape::Tri1)
    {   // Point down left
        b2Vec2 vs[3];
        vs[0].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetYDown) / PPM);
        vs[1].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetY) / PPM);
        vs[2].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetYDown) / PPM);
        m_chainShape.CreateLoop(vs, 3);
        getBody()->CreateFixture(&m_chainShape, 0.f);
    }
    else if (shape == Shape::Tri2)
    {
        // Point up right
        b2Vec2 vs[3];
        vs[0].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetY) / PPM);
        vs[1].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetY) / PPM);
        vs[2].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetYDown) / PPM);
        m_chainShape.CreateLoop(vs, 3);
        getBody()->CreateFixture(&m_chainShape, 0.f);
    }
    else if (shape == Shape::Tri3)
    {
        // Point up left
        b2Vec2 vs[3];
        vs[0].Set((endPos.x - floorOffsetX) / PPM, (endPos.y + floorOffsetY) / PPM);
        vs[1].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetY) / PPM);
        vs[2].Set((startPos.x - floorOffsetX) / PPM, (startPos.y + floorOffsetYDown) / PPM);
        m_chainShape.CreateLoop(vs, 3);
        getBody()->CreateFixture(&m_chainShape, 0.f);
    }
}

const b2Vec2* ChainedObject::getVertices() const
{   
    return m_chainShape.m_vertices;
}

int32 ChainedObject::getVerticesAmount() const
{
    return m_chainShape.m_count;
}
