#pragma once

#include "GameObject.h"

class StaticObject : public GameObject {
public:
    StaticObject(const sf::Texture& texture, const sf::Vector2f& position, bool hasPhysics);
    StaticObject(const sf::Sprite& texture, const sf::Vector2f& position, bool hasPhysics);
    StaticObject(const sf::Vector2f& position, bool hasPhysics);
    virtual void update(float) override;
    virtual void render(sf::RenderWindow& window) const override;
    b2Body* getBody() const;
    bool hasPhysics() const;

protected:
    void setBody(b2Body* body);

private:
    b2Body* m_body;
    bool m_hasPhysics = false;
};