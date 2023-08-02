#include "SkeletonRanged.h"
#include "RoamingState.h"
#include "ChasingState.h"
#include "AttackingState.h"
#include "Weapon.h"

SkeletonRanged::SkeletonRanged(const std::vector<sf::Sprite>& animation, float interval, const sf::Vector2f& position, float velocity, b2World* world)
    :   Mob(animation, interval, velocity, world, SoundManager::instance().getArrowShot(), WeaponType::Arrow, SKELETON_YOFFSET_POS, SKELETON_DAMAGE, SKELE_RANGED_ATTACK_COOLDOWN, SKELETON_HEALTH),
        m_death(SoundManager::instance().getSkeletonDeath()),
        m_hurt(SoundManager::instance().getSkeletonDeath())
{
    // Create Box2D body and fixtures for the moving object
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / PPM, position.y / PPM);
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    // Create the shape for the character's body
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(SKELETON_BODY_WIDTH / 2.f / PPM,
                       SKELETON_BODY_HEIGHT / 2.f / PPM);

    // Create the fixture definition for the body
    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.density = 0.3f; // Set the density of the body
    bodyFixtureDef.friction = 1.f; // Set the friction of the body
    bodyFixtureDef.restitution = 0.f;
    bodyFixtureDef.shape = &bodyShape;

    setBody(world->CreateBody(&bodyDef));

    // Create the fixture for the body in the Box2D body
    getBody()->CreateFixture(&bodyFixtureDef);

    m_mobState = std::make_unique<RoamingState>(SKELETON_DIR_INTERVAL,
        [&](Mob& mob) {
            mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
        },
        [&](Mob& mob) {
            mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Run)), WALK);
        });

    // Set the body to animated sprites
    setAnimationBody();
}

void SkeletonRanged::update(float deltaTime)
{
    updateWeapons(deltaTime);

    sf::Vector2f skeletonPos{ getBody()->GetPosition().x * PPM,
             WINDOW_HEIGHT - (getBody()->GetPosition().y * PPM) };

    if (isAlive() && getOperation() != Operation::Hurt)
    {   // Different states (change per distance)
        if (m_stateID == MobStateID::Roam)
        {
            if (std::abs(m_playersPosition.y - skeletonPos.y) <= 22.f &&
                std::abs(m_playersPosition.x - skeletonPos.x) <= 120.f &&
                std::abs(m_playersPosition.x - skeletonPos.x) >= 105.f)
            {
                m_mobState = std::make_unique<ChasingState>(
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Run)), WALK);
                    });
                m_stateID = MobStateID::Chase;
            }
            else if (std::abs(m_playersPosition.y - skeletonPos.y) <= 22.f &&
                std::abs(m_playersPosition.x - skeletonPos.x) < 105.f)
            {
                m_mobState = std::make_unique<AttackingState>(SKELE_RANGED_ATTACK_COOLDOWN,
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
                    },
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Attack)), SKELE_SHOT);
                    });
                m_stateID = MobStateID::Attack;
                setOperation(Operation::Stay);
                setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
            }
        }
        else if (m_stateID == MobStateID::Chase)
        {
            if (std::abs(m_playersPosition.y - skeletonPos.y) <= 22.f &&
                std::abs(m_playersPosition.x - skeletonPos.x) < 105.f)
            {
                m_mobState = std::make_unique<AttackingState>(SKELE_RANGED_ATTACK_COOLDOWN,
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
                    },
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Attack)), SKELE_SHOT);
                    });
                m_stateID = MobStateID::Attack;
                setOperation(Operation::Stay);
                setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
            }
            else if (std::abs(m_playersPosition.y - skeletonPos.y) > 22.f ||
                     std::abs(m_playersPosition.x - skeletonPos.x > 120.f))
            {
                m_mobState = std::make_unique<RoamingState>(SKELETON_DIR_INTERVAL,
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
                    },
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Run)), WALK);
                    });
                m_stateID = MobStateID::Roam;
            }
        }
        else if (m_stateID == MobStateID::Attack)
        {
            if (std::abs(m_playersPosition.y - skeletonPos.y) > 22.f ||
                std::abs(m_playersPosition.x - skeletonPos.x) > 120.f)
            {
                m_mobState = std::make_unique<RoamingState>(SKELETON_DIR_INTERVAL,
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
                    },
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Run)), WALK);
                    });
                m_stateID = MobStateID::Roam;
                setOperation(Operation::Stay);
                setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
            }
            else if (std::abs(m_playersPosition.y - skeletonPos.y) <= 22.f &&
                std::abs(m_playersPosition.x - skeletonPos.x) <= 105.f &&
                std::abs(m_playersPosition.x - skeletonPos.x) >= 120.f)
            {
                m_mobState = std::make_unique<ChasingState>(
                    [&](Mob& mob) {
                        mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Run)), WALK);
                    });
                m_stateID = MobStateID::Chase;
                setOperation(Operation::Stay);
                setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
            }
        }
        // Inner state update
        m_mobState->update(*this, deltaTime);
    }
    else if (getOperation() == Operation::Hurt)
    {
        m_hurtElapsedTime += deltaTime;

        if (!m_hurtPlayed) // Play hurt sound
        {
            m_hurt.play();
            m_hurtPlayed = true;
        }

        if (m_hurtElapsedTime > 0.4f) // Finish animation after 0.4 sec
        {
            setOperation(Operation::Stay);
            m_mobState = std::make_unique<RoamingState>(SKELETON_DIR_INTERVAL,
                [&](Mob& mob) {
                    mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
                },
                [&](Mob& mob) {
                    mob.setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Run)), WALK);
                });
            m_stateID = MobStateID::Roam;
            m_hurtElapsedTime = 0.f;
            m_hurtPlayed = false;
        }
    }
    else // Skeleton is dead
    {
        setOperation(Operation::Die);
        setAnimation(TextureManager::instance().getSkeletonRangedAnimation(getAnimation().animationID(AnimationType::Die)), SKELE_DIE);
        if (!m_deathPlayed) // Playe death sound once
        {
            m_death.play();
            m_deathPlayed = true;
        }
    }
    // Update with generic moving character
    MovingCharacter::update(deltaTime);
}

void SkeletonRanged::setVolume()
{
    float soundFxVol{ SoundManager::instance().getSoundFxVol() };
    m_death.setVolume(soundFxVol);
    m_hurt.setVolume(soundFxVol);
}