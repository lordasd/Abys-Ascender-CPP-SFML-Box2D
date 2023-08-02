#include "Player.h"
#include "CollisionHandling.h"

Player::Player(const std::vector<sf::Sprite>& animation, float interval, const sf::Vector2f& position, float velocity, b2World* world)
	:   MovingCharacter(animation, interval, velocity, CHARACTER_YOFFSET_POS, world, CHARACTER_HEALTH),
        m_hit(SoundManager::instance().getDamagePlayer()), m_swordHit(SoundManager::instance().getSwordHitPlayer()),
        m_swordWoosh(SoundManager::instance().getSwordWooshPlayer()), m_death(SoundManager::instance().getDeathPlayer()),
        m_jump(SoundManager::instance().getJumpPlayer()), m_land(SoundManager::instance().getLandPlayer()),
        m_shout(SoundManager::instance().getShoutPlayer()), m_eat(SoundManager::instance().getEatPlayer())
{
    // Create Box2D body and fixtures for the moving object
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / PPM, position.y / PPM);
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    // Create the shape for the character's body
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(CHARACTER_BODY_WIDTH / 2.f / PPM,
                       CHARACTER_BODY_HEIGHT / 2.f / PPM);

    // Create the fixture definition for the body
    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.density = 0.3f; // Set the density of the body
    bodyFixtureDef.friction = 1.f; // Set the friction of the body
    bodyFixtureDef.restitution = 0.f;
    bodyFixtureDef.shape = &bodyShape;

    setBody(world->CreateBody(&bodyDef));

    // Create the fixture for the body in the Box2D body
    getBody()->CreateFixture(&bodyFixtureDef);
    
    // Set the body to animated sprites
    setAnimationBody();
}

void Player::attack(float)
{
    if (m_attackElapsed >= 0.6f)
    {
        m_swordWoosh.play(); // Swing the sword
        sf::Vector2f playerPos{ getBody()->GetPosition().x * PPM,
                                getBody()->GetPosition().y * PPM };
        m_swordProjectile.emplace_back(std::make_unique<Sword>(getDirection(), playerPos, getWorld()));
        
        m_attackElapsed = 0;
    }
}

void Player::update(float deltaTime)
{ 
    updateSword(deltaTime); // Weapon

    // Get the current velocity
    b2Vec2 currentVelocity = getBody()->GetLinearVelocity();
    m_jumpElapsed += deltaTime;
    m_attackElapsed += deltaTime;

    if (currentVelocity.y < -3.f)
        setIsOnGround(false);

    // Apply forces or impulses based on input
    if (isOnGround() && isAlive())
    {
        checkHeldKeys(); // Check for held keys(Multiple keys)

        if (getOperation() == Operation::Run && currentVelocity.y > -3.f)
            runOperation(currentVelocity);
        else if (getOperation() == Operation::Jump)
            jumpOperation(currentVelocity);
        else if (getOperation() == Operation::Falling && currentVelocity.y > -3.f) // If we landed change back to stay
            landOnGroundOperation();
        else if (currentVelocity.y < -3.f) // If just walked of an edge, fall
            fallOperation(currentVelocity);
        else if (getOperation() == Operation::Attack)
            attackOperation(deltaTime);
        else if (getOperation() == Operation::Hurt && m_isHurt)
            hurtOperation(deltaTime);
        else // Default
            defaultOperation(currentVelocity);
    }
    else if (getOperation() == Operation::Hurt && m_isHurt)
        hurtOperation(deltaTime);
    else if (getOperation() == Operation::Die && !isAlive())
        deathOperation();
    else if (currentVelocity.y < 0.f) // If falling, set animation to falling
        fallOperation(currentVelocity);

    // Update the animation
    getAnimation().update(deltaTime);
}

bool Player::isHurt() const
{
    return m_isHurt;
}

void Player::setHurt(size_t damage)
{
    setOperation(Operation::Hurt);
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Hurt)), HURT);
    m_isHurt = true;
    hurt(damage);
    if (!isAlive())
    {
        setOperation(Operation::Die);
        setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Die)), DIE);
    }
    m_hit.play();
}

sf::Vector2f Player::getPosition() const
{
    return sf::Vector2f(getBody()->GetPosition().x * PPM,
                        WINDOW_HEIGHT - (getBody()->GetPosition().y * PPM));
}

void Player::setVolume()
{
    float soundFxVol{ SoundManager::instance().getSoundFxVol() };
    m_hit.setVolume(soundFxVol);
    m_swordHit.setVolume(soundFxVol);
    m_swordWoosh.setVolume(soundFxVol);
    m_death.setVolume(soundFxVol);
    m_jump.setVolume(soundFxVol);
    m_land.setVolume(soundFxVol);
    m_shout.setVolume(soundFxVol);
    m_eat.setVolume(soundFxVol);
}

void Player::eat()
{
    m_eat.play();
    addHealth();
}

void Player::touchFinishLine()
{
    m_touchedFinishLine = true;
}

bool Player::isTouchedFinishLine() const
{
    return m_touchedFinishLine;
}

void Player::checkHeldKeys()
{
    // If just fell and touched the ground while pressing on the keyboard
    if ((getOperation() == Operation::Falling && getBody()->GetLinearVelocity().y == 0) ||
        getOperation() == Operation::Attack)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (getOperation() == Operation::Falling) m_land.play();
            setDirection(Direction::Left);
            setOperation(Operation::Run);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (getOperation() == Operation::Falling) m_land.play();
            setDirection(Direction::Right);
            setOperation(Operation::Run);
        }
    }
}

void Player::updateSword(float deltaTime)
{
    for (auto it = m_swordProjectile.begin(); it != m_swordProjectile.end();)
    {
        if (*it)
        {
            Weapon& m_weapon = static_cast<Weapon&>(*it->get());
            if (m_weapon.isHit())
            {
                m_weapon.getBody()->SetAwake(false); // Set body physics false
                getWorld()->DestroyBody(m_weapon.getBody()); // Destroy body
                it = m_swordProjectile.erase(it); // Erase the element from the vector and advance the iterator
                continue; // Skip the rest of the loop body since the iterator has been advanced
            }
            else
                m_weapon.update(deltaTime);
        }

        ++it; // Increment the iterator
    }
}

void Player::runOperation(const b2Vec2& currentVelocity)
{
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Run)), RUN);

    if (getDirection() == Direction::Left)
    {
        b2Vec2 force(-getVelocity(), 0.0f); // Set force
        if (currentVelocity.x > -CHARACTER_MAX_SPEED) // Check max speed in the x direction
            getBody()->ApplyForceToCenter(force, true);
    }
    else if (getDirection() == Direction::Right)
    {
        b2Vec2 force(getVelocity(), 0.0f); // Set force
        if (currentVelocity.x < CHARACTER_MAX_SPEED) // Check max speed in the x direction
            getBody()->ApplyForceToCenter(force, true);
    }
}

void Player::jumpOperation(const b2Vec2& currentVelocity)
{
    if (m_jumpElapsed > 0.5f) // Take care of multiple jumps at the same moment
    {
        m_jump.play();
        setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Jump)), JUMP);
        setIsOnGround(false); // Set jumping

        // Set forward impulse for the jump if *moving*
        float forwardImpulse{};
        if (currentVelocity.x > 0)
            forwardImpulse = 0.4f;
        else if (currentVelocity.x < 0)
            forwardImpulse = -0.4f;
        // Apply an upward impulse to initiate the jump
        b2Vec2 impulse(forwardImpulse, getJumpForce());
        getBody()->ApplyLinearImpulseToCenter(impulse, true);
        m_jumpElapsed = 0.f;
    }
}

void Player::landOnGroundOperation()
{
    m_land.play(); // Play landing sound
    if (m_highestFallingVelocityY >= -10.f)
    {
        setOperation(Operation::Stay);
        setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
    }
    else if (m_highestFallingVelocityY < -10.f && m_highestFallingVelocityY >= -15.f) // Fall from a high level
    {
        setOperation(Operation::Hurt);
        setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Hurt)), HURT);
        setHurt(CHARACTER_FALL_DAMAGE);
        m_highestFallingVelocityY = 0.f;
        m_shout.stop(); // Stop shouting if landed
        m_shouted = false; // Let the player shout again
    }
    else // Die from fall
    {
        setOperation(Operation::Die);
        setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Die)), DIE);
        hurt(6);
    }
}

void Player::fallOperation(const b2Vec2& currentVelocity)
{
    setOperation(Operation::Falling);
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Fall)), FALLING);

    // Apply an opposing force or impulse to stop movement
    b2Vec2 opposingForce = b2Vec2(-currentVelocity.x * getDampingFactor().x, 0.f);
    getBody()->ApplyForceToCenter(opposingForce, true);
    if (currentVelocity.y < m_highestFallingVelocityY) // Set highest falling speed
        m_highestFallingVelocityY = currentVelocity.y;

    if (isOnGround())
    {
        if (currentVelocity.y <= -10.f)
            setIsOnGround(false);
    }
    else
    {
        // If fallen of the map, die
        if (getBody()->GetPosition().y < 0)
        {
            if (isAlive())
            {
                setOperation(Operation::Die);
                hurt(6);
            }
        }
        if (currentVelocity.y < -10.f && !m_shouted) // Shout if falling to fast
        {
            m_shout.play();
            m_shouted = true;
        }
    }
}

void Player::attackOperation(float deltaTime)
{
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Attack)), ATTACK);
    attack(deltaTime);
}

void Player::hurtOperation(float deltaTime)
{
    m_hurtElapsed += deltaTime;
    setOperation(Operation::Hurt);
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Hurt)), HURT);
    if (m_hurtElapsed > 0.6f) // Cancle hurt animation after 0.6 seconds
    {
        setOperation(Operation::Stay);
        setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
        m_hurtElapsed = 0.f;
        m_isHurt = false;
    }
}

void Player::deathOperation()
{
    if (!m_deathSounded)
    {
        m_death.play();
        m_deathSounded = true;
    }
    setOperation(Operation::Die);
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Die)), DIE);
}

void Player::defaultOperation(const b2Vec2& currentVelocity)
{
    setAnimation(TextureManager::instance().getAdventurerAnimation(getAnimation().animationID(AnimationType::Stay)), IDLE2);
    // Apply an opposing force or impulse to stop movement
    b2Vec2 opposingForce = b2Vec2(-currentVelocity.x * getDampingFactor().x, 0.f);
    getBody()->ApplyForceToCenter(opposingForce, true);
}
