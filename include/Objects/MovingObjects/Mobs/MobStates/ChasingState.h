#pragma once 

#include "MobState.h"

class ChasingState : public MobState {
public:
    ChasingState(const std::function<void(Mob&)>& animationWalk);
    void update(Mob& mob, float deltaTime) override;

private:
    float m_startWalking{0.f};
    std::function<void(Mob&)> m_animationWalk;
};