
#pragma once
#include "Entity.h"
#include "Building.h"
#include "ResDefs.h"
#include "ShapeDefs.h"



class PhysicsSystem {
private:
	float closestPoint(float, float, float);
public:
	PhysicsSystem();
	~PhysicsSystem();
	bool SenseCollision(Entity& a_ent, Entity& a_ent2);
	bool SenseCollision(Entity& a_ent, Building& a_building);
	bool ResolveCollision(Entity& a_ent, Entity& a_ent2);
	bool ResolveCollision(Entity& a_ent, Building& a_building);
};
