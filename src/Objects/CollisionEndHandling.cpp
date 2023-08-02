#include "CollisionHandling.h"
#include "Player.h"
#include "Spikes.h"
#include "ChainedObject.h"
#include "SkeletonMelee.h"
#include "SkeletonRanged.h"
#include "ElevatorPlatform.h"
#include "SidePlatform.h"
#include "Drop.h"
#include "FinishLine.h"
#include "Sword.h"
#include "Arrow.h"
#include "Barrel.h"

namespace // anonymous namespace — the standard way to make function "static"
{
    void playerSpikes(GameObject& player, GameObject&)
    {
        Player& m_player = static_cast<Player&>(player);
        m_player.addToCollision(-1);
    }

    void playerFloor(GameObject& player, GameObject& floor)
    {
        Player& m_player = static_cast<Player&>(player);
        ChainedObject& m_object = static_cast<ChainedObject&>(floor);
        m_player.addToCollision(-1);

        // Calculate the bottom edge y position of the player
        float playersBottomY = (WINDOW_HEIGHT - (m_player.getBody()->GetPosition().y * PPM)) + (CHARACTER_BODY_HEIGHT / 2.f);
        // Get vertices of the floor/wall
        const b2Vec2* vertices = m_object.getVertices();
        int32 amount = m_object.getVerticesAmount();
        // Set first lowest y and x
        float lowestY = vertices[0].y;

        // Find the lowest y and corresponding x among the vertices
        for (size_t i = 1; i < amount; ++i)
            if (vertices[i].y < lowestY)
                lowestY = vertices[i].y;

        // Meters to pixels
        lowestY = WINDOW_HEIGHT - (lowestY * PPM) - 10.f;

        if (playersBottomY < lowestY &&
           (m_player.getOperation() == Operation::Jump || m_player.getOperation() == Operation::Stay))
        {
            m_player.addFloorsTouching(-1);
            if(m_player.getCollisions() == 0)
                m_player.setIsOnGround(false);
        }
    }

    void skeletonMeleeFloor(GameObject& skeleton, GameObject& floor)
    {
        SkeletonMelee& m_skeleton = static_cast<SkeletonMelee&>(skeleton);
        ChainedObject& m_object = static_cast<ChainedObject&>(floor);
        m_skeleton.addToCollision(-1);

        // Calculate the bottom edge y position of the skeleton
        float skeletonsBottomY = (WINDOW_HEIGHT - (m_skeleton.getBody()->GetPosition().y * PPM)) + (SKELETON_BODY_HEIGHT / 2.f);
        // Get vertices of the floor/wall
        const b2Vec2* vertices = m_object.getVertices();
        int32 amount = m_object.getVerticesAmount();
        // Set first lowest y and x
        float lowestY = vertices[0].y;

        // Find the lowest y and corresponding x among the vertices
        for (size_t i = 1; i < amount; ++i)
            if (vertices[i].y < lowestY)
                lowestY = vertices[i].y;

        // Meters to pixels
        lowestY = WINDOW_HEIGHT - (lowestY * PPM) - 10.f;

        if (skeletonsBottomY < lowestY &&
            (m_skeleton.getOperation() == Operation::Jump || m_skeleton.getOperation() == Operation::Stay))
        {
            m_skeleton.addFloorsTouching(-1);
            if (m_skeleton.getCollisions() == 0)
                m_skeleton.setIsOnGround(false);
        }
    }

    void skeletonRangedFloor(GameObject& skeleton, GameObject& floor)
    {
        SkeletonRanged& m_skeleton = static_cast<SkeletonRanged&>(skeleton);
        ChainedObject& m_object = static_cast<ChainedObject&>(floor);
        m_skeleton.addToCollision(-1);

        // Calculate the bottom edge y position of the skeleton
        float skeletonsBottomY = (WINDOW_HEIGHT - (m_skeleton.getBody()->GetPosition().y * PPM)) + (SKELETON_BODY_HEIGHT / 2.f);
        // Get vertices of the floor/wall
        const b2Vec2* vertices = m_object.getVertices();
        int32 amount = m_object.getVerticesAmount();
        // Set first lowest y and x
        float lowestY = vertices[0].y;

        // Find the lowest y and corresponding x among the vertices
        for (size_t i = 1; i < amount; ++i)
            if (vertices[i].y < lowestY)
                lowestY = vertices[i].y;

        // Meters to pixels
        lowestY = WINDOW_HEIGHT - (lowestY * PPM) - 10.f;

        if (skeletonsBottomY < lowestY &&
            (m_skeleton.getOperation() == Operation::Jump || m_skeleton.getOperation() == Operation::Stay))
        {
            m_skeleton.addFloorsTouching(-1);
            if (m_skeleton.getCollisions() == 0)
                m_skeleton.setIsOnGround(false);
        }
    }

    void skeletonMeleePlayer(GameObject& skeleton, GameObject&)
    {
        SkeletonMelee& m_skeleton = static_cast<SkeletonMelee&>(skeleton);
        m_skeleton.addToCollision(-1);
    }

    void skeletonRangedPlayer(GameObject& skeleton, GameObject&)
    {
        SkeletonRanged& m_skeleton = static_cast<SkeletonRanged&>(skeleton);
        m_skeleton.addToCollision(-1);
    }

    void skeletonMeleeSpikes(GameObject& skeleton, GameObject&)
    {
        SkeletonMelee& m_skeleton = static_cast<SkeletonMelee&>(skeleton);
        m_skeleton.addToCollision(-1);
    }

    void skeletonRangedSpikes(GameObject& skeleton, GameObject&)
    {
        SkeletonRanged& m_skeleton = static_cast<SkeletonRanged&>(skeleton);
        m_skeleton.addToCollision(-1);
    }

    void playerElevator(GameObject& player, GameObject& elevator)
    {
        Player& m_player = static_cast<Player&>(player);
        ElevatorPlatform& m_object = static_cast<ElevatorPlatform&>(elevator);
        m_player.addToCollision(-1);

        // Calculate the bottom edge y position of the player
        float playersBottomY = (WINDOW_HEIGHT - (m_player.getBody()->GetPosition().y * PPM)) + (CHARACTER_BODY_HEIGHT / 2.f);
        // Get vertices of the floor/wall
        const b2Vec2* vertices = m_object.getVertices();
        int32 amount = m_object.getVerticesAmount();
        // Set first lowest y and x
        float lowestY = vertices[0].y;

        // Find the lowest y and corresponding x among the vertices
        for (size_t i = 1; i < amount; ++i)
            if (vertices[i].y < lowestY)
                lowestY = vertices[i].y;

        // Meters to pixels
        lowestY = WINDOW_HEIGHT - (lowestY * PPM) - 10.f;

        if (playersBottomY < lowestY &&
            (m_player.getOperation() == Operation::Jump || m_player.getOperation() == Operation::Stay))
        {
            m_player.addFloorsTouching(-1);
            if (m_player.getCollisions() == 0)
                m_player.setIsOnGround(false);
        }
    }

    void playerSide(GameObject& player, GameObject& sideplat)
    {
        Player& m_player = static_cast<Player&>(player);
        SidePlatform& m_object = static_cast<SidePlatform&>(sideplat);
        m_player.addToCollision(-1);

        // Calculate the bottom edge y position of the player
        float playersBottomY = (WINDOW_HEIGHT - (m_player.getBody()->GetPosition().y * PPM)) + (CHARACTER_BODY_HEIGHT / 2.f);
        // Get vertices of the floor/wall
        const b2Vec2* vertices = m_object.getVertices();
        int32 amount = m_object.getVerticesAmount();
        // Set first lowest y and x
        float lowestY = vertices[0].y;

        // Find the lowest y and corresponding x among the vertices
        for (size_t i = 1; i < amount; ++i)
            if (vertices[i].y < lowestY)
                lowestY = vertices[i].y;

        // Meters to pixels
        lowestY = WINDOW_HEIGHT - (lowestY * PPM) - 10.f;

        if (playersBottomY < lowestY &&
            (m_player.getOperation() == Operation::Jump || m_player.getOperation() == Operation::Stay))
        {
            m_player.addFloorsTouching(-1);
            if (m_player.getCollisions() == 0)
                m_player.setIsOnGround(false);
        }
    }

    void playerBarrel(GameObject& player, GameObject&)
    {
        Player& m_player = static_cast<Player&>(player);
        m_player.addToCollision(-1);
    }

    // ------------ Collisions without behavior --------------//
    void playerSword(GameObject&, GameObject&) {}
    void playerArrow(GameObject&, GameObject&) {}
    void skeletonMeleeSword(GameObject&, GameObject&) {}
    void skeletonMeleeArrow(GameObject&, GameObject&) {}
    void skeletonRangedSword(GameObject&, GameObject&) {}
    void skeletonRangedArrow(GameObject&, GameObject&) {}
    void floorSword(GameObject&, GameObject&) {}
    void floorArrow(GameObject&, GameObject&) {}
    void floorElevator(GameObject&, GameObject&) {}
    void skeletonMeleeElevator(GameObject&, GameObject&) {}
    void skeletonRangedElevator(GameObject&, GameObject&) {}
    void floorSide(GameObject&, GameObject&) {}
    void skeletonMeleeSide(GameObject&, GameObject&) {}
    void skeletonRangedSide(GameObject&, GameObject&) {}
    void playerDrop(GameObject&, GameObject&) {}
    void skeletonMeleeDrop(GameObject&, GameObject&) {}
    void skeletonRangedDrop(GameObject&, GameObject&) {}
    void elevatorArrow(GameObject&, GameObject&) {}
    void sidePlatArrow(GameObject&, GameObject&) {}
    void elevatorSword(GameObject&, GameObject&) {}
    void sidePlatSword(GameObject&, GameObject&) {}
    void playerFinish(GameObject&, GameObject&) {}
    void skeletonMeleeFinish(GameObject&, GameObject&) {}
    void skeletonRangedFinish(GameObject&, GameObject&) {}
    void swordArrow(GameObject&, GameObject&) {}
    void dropSword(GameObject&, GameObject&) {}
    void swordDrop(GameObject&, GameObject&) {}
    void dropArrow(GameObject&, GameObject&) {}
    void arrowDrop(GameObject&, GameObject&) {}
    void swordBarrel(GameObject&, GameObject&) {}
    void arrowBarrel(GameObject&, GameObject&) {}
    void skeletonMeleeBarrel(GameObject&, GameObject&) {}
    void skeletonRangedBarrel(GameObject&, GameObject&) {}
    void floorBarrel(GameObject&, GameObject&) {}
    void dropBarrel(GameObject&, GameObject&) {}
    void barrelBarrel(GameObject&, GameObject&) {}
    void skeletonRangedSkeletonRanged(GameObject&, GameObject&) {}
    void skeletonMeleeSkeletonMelee(GameObject&, GameObject&) {}
    void barrelSidePlat(GameObject&, GameObject&) {}
    void barrelElevator(GameObject&, GameObject&) {}
    void skeletonMeleeSkeletonRanged(GameObject&, GameObject&) {}
    void spikesBarrel(GameObject&, GameObject&) {}
    
    // -------------- Other side of the collisions --------------//
    void arrowElevator(GameObject& arrow, GameObject& elevator)
    {
        elevatorArrow(elevator, arrow);
    }

    void arrowSidePlat(GameObject& arrow, GameObject& platform)
    {
        sidePlatArrow(platform, arrow);
    }

    void swordElevator(GameObject& sword, GameObject& elevator)
    {
        elevatorSword(elevator, sword);
    }

    void swordSidePlat(GameObject& sword, GameObject& platform)
    {
        sidePlatSword(platform, sword);
    }

    void arrowSword(GameObject& arrow, GameObject& sword)
    {
        swordArrow(sword, arrow);
    }

    void arrowSkeletonRanged(GameObject& arrow, GameObject& skeleton)
    {
        skeletonRangedArrow(skeleton, arrow);
    }

    void swordSkeletonRanged(GameObject& sword, GameObject& skeleton)
    {
        skeletonRangedSword(skeleton, sword);
    }

    void arrowSkeletonMelee(GameObject& arrow, GameObject& skeleton)
    {
        skeletonMeleeArrow(skeleton, arrow);
    }

    void swordSkeletonMelee(GameObject& sword, GameObject& skeleton)
    {
        skeletonMeleeSword(skeleton, sword);
    }

    void arrowPlayer(GameObject& arrow, GameObject& player)
    {
        playerArrow(player, arrow);
    }

    void swordPlayer(GameObject& sword, GameObject& player)
    {
        playerSword(player, sword);
    }

    void finishSkeletonMelee(GameObject& finish, GameObject& skeleton)
    {
        skeletonMeleeFinish(skeleton, finish);
    }

    void finishSkeletonRanged(GameObject& finish, GameObject& skeleton)
    {
        skeletonRangedFinish(skeleton, finish);
    }

    void finishPlayer(GameObject& finish, GameObject& player)
    {
        playerFinish(player, finish);
    }

    void dropSkeletonMelee(GameObject& drop, GameObject& skeleton)
    {
        skeletonMeleeDrop(skeleton, drop);
    }

    void dropSkeletonRanged(GameObject& drop, GameObject& skeleton)
    {
        skeletonRangedDrop(skeleton, drop);
    }

    void dropPlayer(GameObject& drop, GameObject& player)
    {
        playerDrop(player, drop);
    }

    void elevatorSkeletonMelee(GameObject& elevator, GameObject& skeleton)
    {
        skeletonMeleeElevator(skeleton, elevator);
    }

    void elevatorSkeletonRanged(GameObject& elevator, GameObject& skeleton)
    {
        skeletonRangedElevator(skeleton, elevator);
    }

    void elevatorFloor(GameObject& elevator, GameObject& floor)
    {
        floorElevator(floor, elevator);
    }

    void elevatorPlayer(GameObject& platform, GameObject& player)
    {
        playerElevator(player, platform);
    }

    void sideSkeletonMelee(GameObject& elevator, GameObject& skeleton)
    {
        skeletonMeleeSide(skeleton, elevator);
    }

    void sideSkeletonRanged(GameObject& elevator, GameObject& skeleton)
    {
        skeletonRangedSide(skeleton, elevator);
    }

    void sideFloor(GameObject& elevator, GameObject& floor)
    {
        floorSide(floor, elevator);
    }

    void sidePlayer(GameObject& platform, GameObject& player)
    {
        playerSide(player, platform);
    }

    void spikesSkeletonMelee(GameObject& spikes, GameObject& skeleton)
    {
        skeletonMeleeSpikes(skeleton, spikes);
    }

    void spikesSkeletonRanged(GameObject& spikes, GameObject& skeleton)
    {
        skeletonRangedSpikes(skeleton, spikes);
    }

    void playerSkeletonMelee(GameObject& player, GameObject& skeleton)
    {
        skeletonMeleePlayer(skeleton, player);
    }

    void playerSkeletonRanged(GameObject& player, GameObject& skeleton)
    {
        skeletonRangedPlayer(skeleton, player);
    }

    void floorSkeletonMelee(GameObject& floor, GameObject& skeleton)
    {
        skeletonMeleeFloor(skeleton, floor);
    }

    void floorSkeletonRanged(GameObject& floor, GameObject& skeleton)
    {
        skeletonRangedFloor(skeleton, floor);
    }

    void floorPlayer(GameObject& floor, GameObject& player)
    {
        playerFloor(player, floor);
    }

    void spikesPlayer(GameObject& spikes, GameObject& player)
    {
        playerSpikes(player, spikes);
    }

    void swordFloor(GameObject& sword, GameObject& floor)
    {
        floorSword(floor, sword);
    }

    void arrowFloor(GameObject& arrow, GameObject& floor)
    {
        floorArrow(floor, arrow);
    }

    void barrelSword(GameObject& barrel, GameObject& sword)
    {
        swordBarrel(sword, barrel);
    }
    void barrelArrow(GameObject& barrel, GameObject& arrow)
    {
        arrowBarrel(arrow, barrel);
    }
    void barrelPlayer(GameObject& barrel, GameObject& player)
    {
        playerBarrel(player, barrel);
    }
    void barrelSkeletonMelee(GameObject& barrel, GameObject& skeleton)
    {
        skeletonMeleeBarrel(skeleton, barrel);
    }
    void barrelSkeletonRanged(GameObject& barrel, GameObject& skeleton)
    {
        skeletonRangedBarrel(skeleton, barrel);
    }
    void barrelFloor(GameObject& barrel, GameObject& floor)
    {
        floorBarrel(floor, barrel);
    }
    void barrelDrop(GameObject& barrel, GameObject& drop)
    {
        dropBarrel(drop, barrel);
    }

    void sidePlatBarrel(GameObject& platform, GameObject& barrel)
    {
        barrelSidePlat(barrel, platform);
    }

    void elevatorBarrel(GameObject& platform, GameObject& barrel)
    {
        barrelElevator(barrel, platform);
    }

    void skeletonRangedSkeletonMelee(GameObject& skeletonR, GameObject& skeletonM)
    {
        skeletonMeleeSkeletonRanged(skeletonM, skeletonR);
    }

    void barrelSpikes(GameObject& barrel, GameObject& spikes)
    {
        spikesBarrel(spikes, barrel);
    }

    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Player), typeid(Spikes))] = &playerSpikes;
        phm[Key(typeid(Spikes), typeid(Player))] = &spikesPlayer;
        phm[Key(typeid(Player), typeid(Sword))] = &playerSword;
        phm[Key(typeid(Sword), typeid(Player))] = &swordPlayer;
        phm[Key(typeid(Player), typeid(Arrow))] = &playerArrow;
        phm[Key(typeid(Arrow), typeid(Player))] = &arrowPlayer;
        phm[Key(typeid(Sword), typeid(Arrow))] = &swordArrow;
        phm[Key(typeid(Arrow), typeid(Sword))] = &arrowSword;
        phm[Key(typeid(Drop), typeid(Sword))] = &dropSword;
        phm[Key(typeid(Sword), typeid(Drop))] = &swordDrop;
        phm[Key(typeid(Drop), typeid(Arrow))] = &dropArrow;
        phm[Key(typeid(Arrow), typeid(Drop))] = &arrowDrop;
        phm[Key(typeid(Sword), typeid(Barrel))] = &swordBarrel;
        phm[Key(typeid(Barrel), typeid(Sword))] = &barrelSword;
        phm[Key(typeid(Arrow), typeid(Barrel))] = &arrowBarrel;
        phm[Key(typeid(Barrel), typeid(Arrow))] = &barrelArrow;
        phm[Key(typeid(Player), typeid(Barrel))] = &playerBarrel;
        phm[Key(typeid(Barrel), typeid(Player))] = &barrelPlayer;
        phm[Key(typeid(SkeletonMelee), typeid(Barrel))] = &skeletonMeleeBarrel;
        phm[Key(typeid(Barrel), typeid(SkeletonMelee))] = &barrelSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(Barrel))] = &skeletonRangedBarrel;
        phm[Key(typeid(Barrel), typeid(SkeletonRanged))] = &barrelSkeletonRanged;
        phm[Key(typeid(ChainedObject), typeid(Barrel))] = &floorBarrel;
        phm[Key(typeid(Barrel), typeid(ChainedObject))] = &barrelFloor;
        phm[Key(typeid(Drop), typeid(Barrel))] = &dropBarrel;
        phm[Key(typeid(Barrel), typeid(Drop))] = &barrelDrop;
        phm[Key(typeid(Barrel), typeid(Barrel))] = &barrelBarrel;
        phm[Key(typeid(Barrel), typeid(SidePlatform))] = &barrelSidePlat;
        phm[Key(typeid(SidePlatform), typeid(Barrel))] = &sidePlatBarrel;
        phm[Key(typeid(Barrel), typeid(ElevatorPlatform))] = &barrelElevator;
        phm[Key(typeid(ElevatorPlatform), typeid(Barrel))] = &elevatorBarrel;
        phm[Key(typeid(Spikes), typeid(Barrel))] = &spikesBarrel;
        phm[Key(typeid(Barrel), typeid(Spikes))] = &barrelSpikes;
        phm[Key(typeid(SkeletonMelee), typeid(SkeletonMelee))] = &skeletonMeleeSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(SkeletonRanged))] = &skeletonRangedSkeletonRanged;
        phm[Key(typeid(SkeletonMelee), typeid(SkeletonRanged))] = &skeletonMeleeSkeletonRanged;
        phm[Key(typeid(SkeletonRanged), typeid(SkeletonMelee))] = &skeletonRangedSkeletonMelee;
        phm[Key(typeid(ElevatorPlatform), typeid(Arrow))] = &elevatorArrow;
        phm[Key(typeid(Arrow), typeid(ElevatorPlatform))] = &arrowElevator;
        phm[Key(typeid(SidePlatform), typeid(Arrow))] = &sidePlatArrow;
        phm[Key(typeid(Arrow), typeid(SidePlatform))] = &arrowSidePlat;
        phm[Key(typeid(ElevatorPlatform), typeid(Sword))] = &elevatorSword;
        phm[Key(typeid(Sword), typeid(ElevatorPlatform))] = &swordElevator;
        phm[Key(typeid(SidePlatform), typeid(Sword))] = &sidePlatSword;
        phm[Key(typeid(Sword), typeid(SidePlatform))] = &swordSidePlat;
        phm[Key(typeid(ChainedObject), typeid(Sword))] = &floorSword;
        phm[Key(typeid(Sword), typeid(ChainedObject))] = &swordFloor;
        phm[Key(typeid(ChainedObject), typeid(Arrow))] = &floorSword;
        phm[Key(typeid(Arrow), typeid(ChainedObject))] = &swordFloor;
        phm[Key(typeid(SkeletonMelee), typeid(Sword))] = &skeletonMeleeSword;
        phm[Key(typeid(Sword), typeid(SkeletonMelee))] = &swordSkeletonMelee;
        phm[Key(typeid(SkeletonMelee), typeid(Arrow))] = &skeletonMeleeArrow;
        phm[Key(typeid(Arrow), typeid(SkeletonMelee))] = &arrowSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(Sword))] = &skeletonRangedSword;
        phm[Key(typeid(Sword), typeid(SkeletonRanged))] = &swordSkeletonRanged;
        phm[Key(typeid(SkeletonRanged), typeid(Arrow))] = &skeletonRangedArrow;
        phm[Key(typeid(Arrow), typeid(SkeletonRanged))] = &arrowSkeletonRanged;
        phm[Key(typeid(Player), typeid(ChainedObject))] = &playerFloor;
        phm[Key(typeid(ChainedObject), typeid(Player))] = &floorPlayer;
        phm[Key(typeid(SkeletonMelee), typeid(ChainedObject))] = &skeletonMeleeFloor;
        phm[Key(typeid(ChainedObject), typeid(SkeletonMelee))] = &floorSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(ChainedObject))] = &skeletonRangedFloor;
        phm[Key(typeid(ChainedObject), typeid(SkeletonRanged))] = &floorSkeletonRanged;
        phm[Key(typeid(SkeletonMelee), typeid(Player))] = &skeletonMeleePlayer;
        phm[Key(typeid(Player), typeid(SkeletonMelee))] = &playerSkeletonMelee;
        phm[Key(typeid(SkeletonMelee), typeid(Spikes))] = &skeletonMeleeSpikes;
        phm[Key(typeid(Spikes), typeid(SkeletonMelee))] = &spikesSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(Player))] = &skeletonRangedPlayer;
        phm[Key(typeid(Player), typeid(SkeletonRanged))] = &playerSkeletonRanged;
        phm[Key(typeid(SkeletonRanged), typeid(Spikes))] = &skeletonRangedSpikes;
        phm[Key(typeid(Spikes), typeid(SkeletonRanged))] = &spikesSkeletonRanged;
        phm[Key(typeid(Player), typeid(ElevatorPlatform))] = &playerElevator;
        phm[Key(typeid(ElevatorPlatform), typeid(Player))] = &elevatorPlayer;
        phm[Key(typeid(ChainedObject), typeid(ElevatorPlatform))] = &floorElevator;
        phm[Key(typeid(ElevatorPlatform), typeid(ChainedObject))] = &elevatorFloor;
        phm[Key(typeid(SkeletonMelee), typeid(ElevatorPlatform))] = &skeletonMeleeElevator;
        phm[Key(typeid(ElevatorPlatform), typeid(SkeletonMelee))] = &elevatorSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(ElevatorPlatform))] = &skeletonRangedElevator;
        phm[Key(typeid(ElevatorPlatform), typeid(SkeletonRanged))] = &elevatorSkeletonRanged;
        phm[Key(typeid(Player), typeid(SidePlatform))] = &playerSide;
        phm[Key(typeid(SidePlatform), typeid(Player))] = &sidePlayer;
        phm[Key(typeid(ChainedObject), typeid(SidePlatform))] = &floorSide;
        phm[Key(typeid(SidePlatform), typeid(ChainedObject))] = &sideFloor;
        phm[Key(typeid(SkeletonMelee), typeid(SidePlatform))] = &skeletonMeleeSide;
        phm[Key(typeid(SidePlatform), typeid(SkeletonMelee))] = &sideSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(SidePlatform))] = &skeletonRangedSide;
        phm[Key(typeid(SidePlatform), typeid(SkeletonRanged))] = &sideSkeletonRanged;
        phm[Key(typeid(Player), typeid(Drop))] = &playerDrop;
        phm[Key(typeid(Drop), typeid(Player))] = &dropPlayer;
        phm[Key(typeid(SkeletonMelee), typeid(Player))] = &skeletonMeleeDrop;
        phm[Key(typeid(Drop), typeid(SkeletonMelee))] = &dropSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(Player))] = &skeletonRangedDrop;
        phm[Key(typeid(Drop), typeid(SkeletonRanged))] = &dropSkeletonRanged;
        phm[Key(typeid(Player), typeid(FinishLine))] = &playerFinish;
        phm[Key(typeid(FinishLine), typeid(Player))] = &finishPlayer;
        phm[Key(typeid(SkeletonMelee), typeid(FinishLine))] = &skeletonMeleeFinish;
        phm[Key(typeid(FinishLine), typeid(SkeletonMelee))] = &finishSkeletonMelee;
        phm[Key(typeid(SkeletonRanged), typeid(FinishLine))] = &skeletonRangedFinish;
        phm[Key(typeid(FinishLine), typeid(SkeletonRanged))] = &finishSkeletonRanged;

        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processEndCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
        throw UnknownCollision(object1, object2);

    phf(object1, object2);
}