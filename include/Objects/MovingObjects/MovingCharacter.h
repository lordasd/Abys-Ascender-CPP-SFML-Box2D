#pragma once

#include "MovingObject.h"
#include "Animation.h"

class MovingCharacter : public MovingObject{
public:
	MovingCharacter(const std::vector<sf::Sprite>& animation, float interval, float velocity, float yOffset, b2World* world, size_t health);
	virtual void update(float deltaTime) override;
	virtual void render(sf::RenderWindow& window) const override;
	virtual void attack(float deltaTime) = 0;
	virtual void setVolume() = 0;

	Animation& getAnimation();
	const Operation& getOperation() const;
	void setOperation(const Operation& operation);
	float getJumpForce() const;
	bool isOnGround() const;
	void setIsOnGround(bool isOnGround);
	bool isAlive() const;
	void hurt(size_t damage);
	void setAnimation(const std::vector<sf::Sprite>& animation, float interval);
	size_t getHealth() const;

protected:
	void setAnimationBody();
	void addHealth();

private:
	Animation m_animation;
	Operation m_currOperation{ Operation::Stay };
	size_t m_health;
	float m_jumpForce = 3.7f;
	bool m_isOnGround = false;
	sf::Clock m_hurtTime;
};