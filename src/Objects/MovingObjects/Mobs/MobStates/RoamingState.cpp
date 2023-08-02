#include "RoamingState.h"
#include "Mob.h"

RoamingState::RoamingState(float directionChangeInterval, const std::function<void(Mob&)>& animationStay, const std::function<void(Mob&)>& animationWalk)
    :   m_directionChangeInterval(directionChangeInterval), m_animationStay(animationStay), m_animationWalk(animationWalk) {}

void RoamingState::update(Mob& mob, float deltaTime)
{
    // Update the direction change timer
    m_timer += deltaTime;

    // Check if it's time to change the animation
    if (m_timer >= m_directionChangeInterval)
    {
        // Generate a random direction
        Operation newOpeartion = generateNewOperation();

        // Apply the new operation
        mob.setDirection(m_currDirection);
        mob.setOperation(newOpeartion);

        // Update the animation based on the direction
        if (newOpeartion == Operation::Stay)
            m_animationStay(mob);
        else
            m_animationWalk(mob);

        // Reset the direction change timer
        m_timer = 0.0f;
    }
}

Operation RoamingState::generateNewOperation()
{
    // Generate a random number between 0 and 1 (Right, Left, Stay)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);
    int randomIndex = dis(gen);

    if (randomIndex == 0)
    {
        if (m_currDirection == Direction::Right)
            m_currDirection = Direction::Left;
        else m_currDirection = Direction::Right;
        return Operation::Run;
    }
    else
        return Operation::Stay;
}