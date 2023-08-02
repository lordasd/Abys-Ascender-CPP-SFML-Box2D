#pragma once

#include <SFML/Graphics.hpp>

enum class Operation
{
    Run,
    Jump,
    Stay,
    Falling,
    Attack,
    Hurt,
    Die,
    Max
};

enum class Direction
{
    Left,
    Right,
    Up,
    Down,
    Max
};