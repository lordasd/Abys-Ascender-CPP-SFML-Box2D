#pragma once

#include "MovingCharacter.h"
#include "MobState.h"
#include "Weapon.h"

class Mob : public MovingCharacter {
public:
	Mob(const std::vector<sf::Sprite>& animation, float interval, float velocity, b2World* world, const sf::SoundBuffer& attackSound, const WeaponType& weaponType, float yOffset, float damage, float attackCooldown, size_t health);
	virtual void render(sf::RenderWindow& window) const override;
	virtual void attack(float deltaTime) override;
	void setPlayerPosition(const b2Vec2& pos);
	const sf::Vector2f getPlayersPosition() const;
	void setHurt(size_t damage, const std::vector<sf::Sprite>& animation);

protected:
	using Objects = std::vector<std::unique_ptr<GameObject>>;
	Objects m_weaponProjectile;
	std::unique_ptr<MobState> m_mobState;
	MobStateID m_stateID = MobStateID::Roam;
	sf::Vector2f m_playersPosition;
	WeaponType m_weaponType;
	sf::Sound m_attackSound;
	float m_damage;
	float m_attackElapsed{ 1.f };
	float m_attackCoolown;

	void updateWeapons(float deltaTime);
};