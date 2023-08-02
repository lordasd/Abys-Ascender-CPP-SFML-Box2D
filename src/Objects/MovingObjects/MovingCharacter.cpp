#include "MovingCharacter.h"

MovingCharacter::MovingCharacter(const std::vector<sf::Sprite>& animation, float interval, float velocity, float yOffset, b2World* world, size_t health)
    :   MovingObject(animation.back(), velocity, world), m_animation(animation, interval, yOffset), m_health(health) {}

void MovingCharacter::update(float deltaTime)
{
    // Get the current velocity
    b2Vec2 currentVelocity = getBody()->GetLinearVelocity();

    if (isOnGround() && isAlive())
    {
        // Apply forces or impulses based on input
        if (m_currOperation == Operation::Run && getDirection() == Direction::Left)
        {
            b2Vec2 force(-getVelocity(), 0.0f); // Set force
            if (currentVelocity.x > -MAX_SPEED) // Check max speed in the x direction
                getBody()->ApplyForceToCenter(force, true);
        }
        else if (m_currOperation == Operation::Run && getDirection() == Direction::Right)
        {
            b2Vec2 force(getVelocity(), 0.0f); // Set force
            if (currentVelocity.x < MAX_SPEED) // Check max speed in the x direction
                getBody()->ApplyForceToCenter(force, true);
        }
        else
        {
            // Apply an opposing force or impulse to stop movement
            b2Vec2 opposingForce = b2Vec2(-currentVelocity.x * getDampingFactor().x, currentVelocity.y);
            getBody()->ApplyForceToCenter(opposingForce, true);
        }
    }
    else if (!isAlive())
        setOperation(Operation::Die);
    else if (currentVelocity.y < 0) // If falling set animation to falling
    {
        setOperation(Operation::Falling); 
        // Apply an opposing force or impulse to stop movement
        b2Vec2 opposingForce = b2Vec2(-currentVelocity.x * getDampingFactor().x, 0.f);
        getBody()->ApplyForceToCenter(opposingForce, true);
    }

    // Update the animation or perform any other necessary logic
    m_animation.update(deltaTime);
}

void MovingCharacter::render(sf::RenderWindow& window) const
{
    // Render the moving object's animation
    m_animation.render(window);
}

float MovingCharacter::getJumpForce() const
{
    return m_jumpForce;
}

bool MovingCharacter::isOnGround() const
{
    return m_isOnGround;
}

void MovingCharacter::setIsOnGround(bool isOnGround)
{
    m_isOnGround = isOnGround;
}

void MovingCharacter::setAnimationBody()
{
    m_animation.setAnimationBody(getBody());
}

void MovingCharacter::setAnimation(const std::vector<sf::Sprite>& animation, float interval)
{
    m_animation.setAnimation(animation, interval, m_currOperation, getDirection());
}

size_t MovingCharacter::getHealth() const
{
    return m_health;
}

void MovingCharacter::addHealth()
{
    if (m_health < 6)
        ++m_health;
}

Animation& MovingCharacter::getAnimation()
{
    return m_animation;
}

const Operation& MovingCharacter::getOperation() const
{
    return m_currOperation;
}

void MovingCharacter::setOperation(const Operation& operation)
{
    m_currOperation = operation;
}

bool MovingCharacter::isAlive() const
{
    return m_health > 0 ? true : false;
}

void MovingCharacter::hurt(size_t damage)
{
    // Don't allow for a character to get hurt more than once at the same time
    if (m_hurtTime.getElapsedTime().asSeconds() > 0.5f)
    {
        if (m_health >= damage)
            m_health -= damage;
        else
            m_health = 0;
        m_hurtTime.restart();
    }
}
