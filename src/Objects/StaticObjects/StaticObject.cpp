#include "StaticObject.h"

StaticObject::StaticObject(const sf::Texture& texture, const sf::Vector2f& position, bool hasPhysics)
    :  m_hasPhysics(hasPhysics), GameObject(texture, position) {}

StaticObject::StaticObject(const sf::Sprite& texture, const sf::Vector2f& position, bool hasPhysics)
    :  m_hasPhysics(hasPhysics), GameObject(texture, position) {}

StaticObject::StaticObject(const sf::Vector2f& position, bool hasPhysics)
    :   m_hasPhysics(hasPhysics), GameObject(position) {}

void StaticObject::update(float)
{
    if (m_hasPhysics)
    {
        // Update the position and velocity of the moving object based on Box2D physics
        m_sprite.setPosition(m_body->GetPosition().x * PPM,
                             WINDOW_HEIGHT - (m_body->GetPosition().y * PPM));
        m_sprite.setRotation(m_body->GetAngle() * -180.f / b2_pi);
        m_sprite.setOrigin(TILE_SIZE / 2.f, TILE_SIZE / 2.f);
    }
    else
    {
        m_sprite.setPosition(m_position.x, WINDOW_HEIGHT - m_position.y);
        m_sprite.setOrigin(TILE_SIZE / 2.f, TILE_SIZE / 2.f);
    }
}

void StaticObject::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

b2Body* StaticObject::getBody() const
{
    return m_body;
}

bool StaticObject::hasPhysics() const
{
    return m_hasPhysics;
}

void StaticObject::setBody(b2Body* body)
{
    m_body = body;
}
