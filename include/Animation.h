#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.h"
#include <box2d/box2d.h>
#include <iostream>
#include "Operation.h"

enum class AnimationType { Stay, Run, Jump, Fall, Attack, Hurt, Die };

class Animation {
public:
	Animation() = default;
	Animation(const std::vector<sf::Sprite>& animation, float frameDuration, float yOffset);
	void update(float deltaTime);
	void render(sf::RenderWindow& window) const;
	void setAnimationBody(const b2Body* body);
	void setAnimation(const std::vector<sf::Sprite>& animation, float interval, const Operation& operation, const Direction& direction);
	int animationID(const AnimationType& type) const;
	bool isLookingRight() const;

private:
	std::vector<sf::Sprite> m_frames;
	size_t m_currentFrameIndex = 0U;
	float m_frameDuration;
	float m_elapsedTime = 0.f;
	bool m_isPlaying = false;
	const b2Body* m_body;
	Direction m_currDirection = Direction::Right;
	Operation m_currOperation = Operation::Stay;
	bool m_lookingRight = true;
	float m_yOffest;
};