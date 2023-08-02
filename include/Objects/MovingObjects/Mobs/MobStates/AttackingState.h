#pragma once

#include "MobState.h"

class AttackingState : public MobState {
public:
    AttackingState(float attackCooldown, const std::function<void(Mob&)>& animationStay, const std::function<void(Mob&)>& animationAttack);
    void update(Mob& mob, float deltaTime) override;
private:
    float m_elapsedTime{0.4f};
    bool m_attacked = false;
    float m_attackCooldown;
    std::function<void(Mob&)> m_animationIdle;
    std::function<void(Mob&)> m_animationAttack;
};