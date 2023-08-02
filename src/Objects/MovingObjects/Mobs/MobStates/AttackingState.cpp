#include "AttackingState.h"
#include "Mob.h"

AttackingState::AttackingState(float attackCooldown, const std::function<void(Mob&)>& animationStay, const std::function<void(Mob&)>& animationAttack)
	:	m_attackCooldown(attackCooldown), m_animationIdle(animationStay), m_animationAttack(animationAttack) {}

void AttackingState::update(Mob& mob, float deltaTime)
{
    // Update the attack elapsed time
    m_elapsedTime += deltaTime;

    if (m_elapsedTime > m_attackCooldown && !m_attacked)
    {
        if (mob.getPlayersPosition().x < mob.getBody()->GetPosition().x * PPM)
            mob.setDirection(Direction::Left);
        else
            mob.setDirection(Direction::Right);
        mob.setOperation(Operation::Attack);
        m_animationAttack(mob);
        m_attacked = true;
        m_elapsedTime = 0;
    }
    else if (m_attacked && m_elapsedTime > m_attackCooldown - 0.2f)
    {   // Attack only after animation ends(a bit before (0.2f))
        mob.attack(m_elapsedTime);
        mob.setOperation(Operation::Stay);
        m_animationIdle(mob);
        m_attacked = false;
        m_elapsedTime = 0.f;
    }
}