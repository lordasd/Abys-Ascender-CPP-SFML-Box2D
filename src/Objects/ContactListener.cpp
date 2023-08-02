#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    // Get the Box2D bodies involved in the contact
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    // Get the user data from the Box2D bodies (assuming you store GameObject pointers)
    GameObject* objA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
    GameObject* objB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

    // Process the collision using the CollisionHandling class
    processCollision(*objA, *objB);
}

void ContactListener::EndContact(b2Contact* contact)
{
    // Get the Box2D bodies involved in the contact
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    // Get the user data from the Box2D bodies (assuming you store GameObject pointers)
    GameObject* objA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
    GameObject* objB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

    // Process the collision using the CollisionHandling class
    processEndCollision(*objA, *objB);
}
