#pragma once

#include <box2d/box2d.h>
#include <memory>
#include "CollisionHandling.h"

class ContactListener : public b2ContactListener {
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
};