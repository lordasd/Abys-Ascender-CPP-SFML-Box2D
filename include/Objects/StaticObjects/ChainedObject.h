#pragma once

#include "StaticObject.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

enum class Shape { Square, Tri0, Tri1, Tri2, Tri3 };

class ChainedObject : public StaticObject {
public:
	ChainedObject(const sf::Vector2f& position, b2World* world);
	virtual void update(float delta) override;
	void createChain(const sf::Vector2f& startPos, const sf::Vector2f& endPos, const Shape& shape);
	const b2Vec2* getVertices() const;
	int32 getVerticesAmount() const;

private:
	b2ChainShape m_chainShape;
};