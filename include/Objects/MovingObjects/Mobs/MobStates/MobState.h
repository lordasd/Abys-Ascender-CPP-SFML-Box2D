#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <random>
#include "Operation.h"
#include <functional>

enum class MobStateID { Roam, Chase, Attack };

class Mob;

class MobState {
public:
    virtual ~MobState() = default;
    virtual void update(Mob& mob, float deltaTime) = 0;

protected:
    Direction m_currDirection = Direction::Right;
};