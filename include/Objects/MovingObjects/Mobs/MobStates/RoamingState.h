#pragma once

#include "MobState.h"

class RoamingState : public MobState {
public:
    RoamingState(float directionChangeInterval, const std::function<void(Mob&)>& animationStay, const std::function<void(Mob&)>& animationWalk);
    void update(Mob& mob, float deltaTime) override;

private:
    float m_timer = 0.f;
    float m_directionChangeInterval;
    std::function<void(Mob&)> m_animationStay;
    std::function<void(Mob&)> m_animationWalk;

    Operation generateNewOperation();
};