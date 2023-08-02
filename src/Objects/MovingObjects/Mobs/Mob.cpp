#include "Mob.h"
#include "Sword.h"
#include "Arrow.h"

Mob::Mob(const std::vector<sf::Sprite>& animation, float interval, float velocity, b2World* world, const sf::SoundBuffer& attackSound, const WeaponType& weaponType, float yOffset, float damage, float attackCooldown, size_t health)
	:   MovingCharacter(animation, interval, velocity, yOffset, world, health), m_weaponType(weaponType), m_attackSound(attackSound), m_damage(damage), m_attackCoolown(attackCooldown) {}

void Mob::render(sf::RenderWindow& window) const
{
    for (auto& projectile : m_weaponProjectile)
        projectile->render(window);
    MovingCharacter::render(window);
}

void Mob::setPlayerPosition(const b2Vec2& pos)
{
	m_playersPosition = sf::Vector2f(pos.x * PPM, WINDOW_HEIGHT - (pos.y * PPM));
}

const sf::Vector2f Mob::getPlayersPosition() const
{
	return m_playersPosition;
}

void Mob::attack(float deltaTime)
{
    m_attackElapsed += deltaTime;

	if (m_attackElapsed >= m_attackCoolown - 0.2f)
	{
        m_attackSound.play();
        sf::Vector2f mobPos{ getBody()->GetPosition().x* PPM,
                             getBody()->GetPosition().y * PPM };
        if(m_weaponType == WeaponType::Sword) // Sword weapon
            m_weaponProjectile.emplace_back(std::make_unique<Sword>(getDirection(), mobPos, getWorld()));
        else if(m_weaponType == WeaponType::Arrow) // Bow and arrow weapon
            m_weaponProjectile.emplace_back(std::make_unique<Arrow>(TextureManager::instance().getWeaponArrow(), getDirection(), mobPos, getWorld()));
        m_attackElapsed = 0;
	}
}

void Mob::setHurt(size_t damage, const std::vector<sf::Sprite>& animation)
{
    setOperation(Operation::Hurt);
    setAnimation(animation, HURT);
    hurt(damage);   
}

void Mob::updateWeapons(float deltaTime)
{
	for (auto it = m_weaponProjectile.begin(); it != m_weaponProjectile.end();)
	{
		if (*it)
		{
			Weapon& m_weapon = static_cast<Weapon&>(*it->get());
            if (m_weapon.isHit())
            {
                m_weapon.getBody()->SetAwake(false); // Set body physics false
                getWorld()->DestroyBody(m_weapon.getBody()); // Destroy body
                it = m_weaponProjectile.erase(it); // Erase the element from the vector and advance the iterator
                continue; // Skip the rest of the loop body since the iterator has been advanced
            }
            else
                m_weapon.update(deltaTime);
		}

		++it; // Increment the iterator
	}
}

