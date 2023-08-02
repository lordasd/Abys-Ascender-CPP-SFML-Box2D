#pragma once

#include "GameObject.h"
#include "Operation.h"

class MovingObject : public GameObject {
public:
    MovingObject(const sf::Sprite& sprite, float velocity, b2World* world);
    MovingObject(const sf::Sprite& sprite, const sf::Vector2f position, float velocity);
    MovingObject(const sf::Texture& texture, const sf::Vector2f& position, float velocity, b2World* world);
    MovingObject(const sf::Texture& texture, const sf::Vector2f& position, float velocity);
    MovingObject(const sf::Vector2f& position, float velocity);
    virtual void render(sf::RenderWindow& window) const override;

    float getVelocity() const;
    void setVelocity(float velocity);
    const b2Vec2& getDampingFactor() const;
    Direction getDirection() const;
    void setDirection(const Direction& direction);
    b2Body* getBody() const;
    size_t getCollisions() const;
    void addToCollision(int x);
    size_t getFloorsTouching() const;
    void addFloorsTouching(int x);

protected:
    b2World* getWorld() const;
    void setBody(b2Body* body);

private:
    b2Body* m_body;
    b2World* m_world;
    Direction m_currDirection{ Direction::Right };
    float m_velocity;
    b2Vec2 m_dampingFactor = b2Vec2(0.5f, 0.5f);

    size_t m_collisions = 0;
    size_t m_floorsTouching{ 0 };
};