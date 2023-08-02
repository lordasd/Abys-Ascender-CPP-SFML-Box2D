#pragma once

#include "MovingCharacter.h"
#include "Sword.h"

using Objects = std::vector<std::unique_ptr<GameObject>>;

class Player : public MovingCharacter {
public:
	Player(const std::vector<sf::Sprite>& animation, float interval, const sf::Vector2f& position, float velocity, b2World* world);
	void attack(float deltaTime);
	virtual void update(float deltaTime) override;
	bool isHurt() const;
	void setHurt(size_t damage);
	sf::Vector2f getPosition() const;
	void setVolume() override;
	void eat();
	void touchFinishLine();
	bool isTouchedFinishLine() const;

private:
	Objects m_swordProjectile;
	bool m_isHurt{ false };
	float m_hurtElapsed{};
	float m_attackElapsed{1.f};
	float m_jumpElapsed{0.5f};
	float m_highestFallingVelocityY{};
	bool m_shouted = false;
	bool m_deathSounded = false;
	bool m_touchedFinishLine = false;
	sf::Sound m_hit;
	sf::Sound m_swordHit;
	sf::Sound m_swordWoosh;
	sf::Sound m_death;
	sf::Sound m_jump;
	sf::Sound m_land;
	sf::Sound m_shout;
	sf::Sound m_eat;

	void checkHeldKeys();
	void updateSword(float deltaTime);
	void runOperation(const b2Vec2& currentVelocity);
	void jumpOperation(const b2Vec2& currentVelocity);
	void landOnGroundOperation();
	void fallOperation(const b2Vec2& currentVelocity);
	void attackOperation(float deltaTime);
	void hurtOperation(float deltaTime);
	void deathOperation();
	void defaultOperation(const b2Vec2& currentVelocity);
};