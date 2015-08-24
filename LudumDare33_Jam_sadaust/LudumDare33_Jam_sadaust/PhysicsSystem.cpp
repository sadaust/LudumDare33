#pragma once
#include "PhysicsSystem.h"




PhysicsSystem::PhysicsSystem() {

}


PhysicsSystem::~PhysicsSystem() {

}


float PhysicsSystem::closestPoint(float a_point, float a_1, float a_2) {
	if(abs(a_point-a_1) <= abs(a_point-a_2)) {
		return a_1; // returns VVVVVVVVVVVVVVVVVVVV
	}
	else {
		return a_2; // returns point that is closest
	}
}


bool PhysicsSystem::SenseCollision(Entity& a_player, Entity& a_player2) {
	if(a_player.getPos().y < a_player2.getPos().y+a_player2.getBound().height) { // y,y,top
		if(a_player.getPos().y > a_player2.getPos().y-a_player.getBound().height) { //y,y,bottom
			float distX = 0;
			float distZ = 0;
			float tempDist = 0;
			distX = a_player2.getPos().x-a_player.getPos().x;
			distZ = a_player2.getPos().z-a_player.getPos().z;
			// Finds distances in straight lines between the points
			tempDist = (distX*distX)+(distZ*distZ);
			if(tempDist <= a_player2.getBound().radius + a_player.getBound().radius) {
				return true;
			}
		}
	}
	return false;
}

bool PhysicsSystem::SenseCollision(Entity& a_ent, Building& a_build) {
	//2d collison treating player like a cube
	//check if right eadge of player is outside building left edge
	/*if((a_ent.getPos().x+a_ent.getSize())<(a_build.getPos().x+a_build.getCol().left)) {
	//check if left eadge of player is outside building right edge
	if((a_ent.getPos().x-a_ent.getSize())<(a_build.getPos().x+a_build.getCol().right)) {
	if((a_ent.getPos().z+a_ent.getSize())<(a_build.getPos().z+a_build.getCol().back)) {
	if((a_ent.getPos().z-a_ent.getSize())<(a_build.getPos().z+a_build.getCol().front))
	return true;
	}
	}
	}*/

	if(a_ent.getPos().x < a_build.getPos().x+a_build.getCol().right+a_ent.getBound().radius) {//x,x,right
		if(a_ent.getPos().x > a_build.getPos().x+a_build.getCol().left-a_ent.getBound().radius) {//x,x,left
			if(a_ent.getPos().z > a_build.getPos().z+a_build.getCol().back-a_ent.getBound().radius) {//z,z,back
				if(a_ent.getPos().z < a_build.getPos().z+a_build.getCol().front+a_ent.getBound().radius) {//z,z,front
					return true;
				}
			}
		}
	}
	return false;
}


bool  PhysicsSystem::ResolveCollision(Entity& a_player, Entity& a_player2){

	if(a_player.canEat()) {
		if(a_player.getSize() >= a_player2.getSize()) {
			a_player.setSize(a_player.getSize()+a_player2.getSize());
			a_player2.setActive(false);
			return true;
		} else {
			a_player.revPos();
			a_player2.revPos();
		}
	} else {
		a_player.revPos();
		a_player2.revPos();
	}
	return false;
}

bool PhysicsSystem::ResolveCollision(Entity& a_ent, Building& a_build) {
	if(a_ent.canEat()) {
		if(a_ent.getSize()>a_build.getSize()) {
			a_ent.setSize(a_ent.getSize()+a_build.getSize());
			a_build.setActive(false);
			return true;
		} else {
			a_ent.revPos();
		}
	} else {
		a_ent.revPos();
	}
	return false;
}