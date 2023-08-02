#pragma once
#include <string>
#include <box2d/box2d.h>

// Window size
const unsigned int WINDOW_WIDTH = 1024;
const unsigned int WINDOW_HEIGHT = 768;
const unsigned int LEVEL1_WIDTH = 1024;
const unsigned int LEVEL1_HEIGHT = 768;
const unsigned int LEVEL2_WIDTH = 3200;
const unsigned int LEVEL2_HEIGHT = 480;
const unsigned int LEVEL3_WIDTH = 3200;
const unsigned int LEVEL3_HEIGHT = 480;

// Tile size
const float TILE_SIZE = 16.f;
const size_t MAP_WIDTH = 64;
const size_t MAP_HEIGHT = 49;

// Level names
const size_t DotTxt = 5; // length of ".txt"
const std::string SAVEFILE = "save.txt";
const std::string LEVEL1 = "level1.txt";
const std::string LEVEL2 = "level2.txt";
const std::string LEVEL3 = "level3.txt";
const size_t MAX_LEVEL = 3;

// World gravity
const b2Vec2 GRAVITY{0.f, -9.8f};
// Pixels per meter. Box2D uses metric units, so we need to define a conversion
const float PPM = 16.f;
// SFML uses degrees for angles while Box2D uses radians
const float DEG_PER_RAD = 57.2957795f;
// FPS
const float FPS = 1.f / 60.f;
// Velocity Iterations
const int32 VEL_ITER = 8;
// Position Iterations
const int32 POS_ITER = 5;
// MainMenu buttons
const size_t BUTTONS_AMOUNT = 5;

// Offesets for the chained shapes(floor&Walls)
const float floorOffsetX = 8.f;
const float floorOffsetY = 8.f;
const float floorOffsetYDown = -8.f;

// Character sizes
const float CHARACTER_WIDTH = 50.f;
const float CHARACTER_HEIGHT = 37.f;
const float CHARACTER_BODY_WIDTH = CHARACTER_WIDTH - 30.f;
const float CHARACTER_BODY_HEIGHT = CHARACTER_HEIGHT - 8.f;
const size_t CHARACTER_HEALTH = 6;
const size_t CHARACTER_DAMAGE = 1;
const size_t CHARACTER_FALL_DAMAGE = 2;
const float CHARACTER_YOFFSET_POS = 2.f;
const float CHARACTER_VELOCITY = 10.f;

// Skeleton size
const float SKELETON_WIDTH = 64.f;
const float SKELETON_HEIGHT = 64.f;
const float SKELETON_BODY_WIDTH = SKELETON_WIDTH - 40.f;
const float SKELETON_BODY_HEIGHT = SKELETON_WIDTH - 33.f;
const size_t SKELETON_HEALTH = 3;
const size_t SKELETON_DAMAGE = 1;
const size_t SKELETON_TOUCH_DAMAGE = 1;
const float SKELETON_YOFFSET_POS = 16.f;
const float SKELETON_VELOCITY = 10.f;
const float SKELETON_DIR_INTERVAL = 3.f;

// Max speed for moving objects
const float CHARACTER_MAX_SPEED = 3.f;
const float MAX_SPEED = 1.f;
const float PLATFORM_MAX_SPEED = 2.f;

// Animation Frame Inverval
const float IDLE2 = 0.25f;
const float RUN = 0.2f;
const float JUMP = 0.2f;
const float FALLING = 0.2f;
const float ATTACK = 0.1f;
const float HURT = 0.2f;
const float WALK = 0.3f;
const float DIE = 0.5f;

// Skeleton Frame Interval
const float SKELE_WALK = 0.3f;
const float SKELE_DIE = 0.5f;
const float SKELE_ATTACK = 0.1f;
const float SKELE_SHOT = 0.06f;
const float SKELE_HURT = 0.2f;
const float SKELE_MELEE_ATTACK_COOLDOWN = 0.7f;
const float SKELE_RANGED_ATTACK_COOLDOWN = 1.f;

// Spikes
const size_t SPIKE_DAMAGE = 1;

// Moving platform
const float PLATFORM_WIDTH = 64.f;
const float PLATFORM_HEIGHT = 32.f;
const float PLATFORM_VELOCITY = 1.f;
const float PLATFORM_MAX_VELOCITY = 1.f;
const float ELEVATOR_INTERVAL = 6.f;
const float ELEVATOR_INTERVAL_LONG = 9.f;
const float SIDE_INTERVAL = 6.f;

// Drops
const float DROP_WIDTH = 16.f;
const float DROP_HEIGHT = 16.f;
const float DROP_VELOCITY = 0.3f;
const float DROP_INTERVAL = 0.7f;

// Weapons Velocity
const float SWORD_VELOCITY = 1.f;
const float ARROW_VELOCITY = 15.f;

// Weapons Lifetime
const float SWORD_LIFETIME = 0.1f;
const float ARROW_LIFETIME = 1.f;