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


bool  PhysicsSystem::ResolveCollision(Entity& a_player, Entity& a_player2){

	if(a_player.canEat()) {
		if(a_player.getSize() >= a_player2.getSize()) {
			a_player.setSize(a_player.getSize()+a_player2.getSize());
			a_player2.setActive(false);
		} else {
			a_player.revPos();
			a_player2.revPos();
		}
	} else {
		a_player.revPos();
		a_player2.revPos();
	}
	return true;
}

//float Distance2D(float a_x, float a_z, float a_x2, float a_z2) {
//
//}


//bool PlayerWall(D3DXVECTOR3 &a_pos, PrimStruct &a_cube, float a_radius, float a_height) {
//	float tempX = 0, tempZ = 0, tempDist = 0;
//
//	if(a_pos.y <= a_cube.top) {
//		if(a_pos.y+a_height >= a_cube.bottom) {
//			for(int i = 0; i < 4; ++i) {
//				if(i == 0) {
//					tempX = abs(a_pos.x-a_cube.left); // left,front
//					tempZ = abs(a_pos.z-a_cube.front);
//				}
//				else if(i == 1) {
//					tempX = abs(a_pos.x-a_cube.left); // left,back
//					tempZ = abs(a_pos.z-a_cube.back);
//				}
//				else if(i == 2) {
//					tempX = abs(a_pos.x-a_cube.right); // right,back
//					tempZ = abs(a_pos.z-a_cube.back);
//				}
//				else if(i == 3) {
//					tempX = abs(a_pos.x-a_cube.right); // right,front
//					tempZ = abs(a_pos.z-a_cube.front);
//				}
//				tempDist = tempX*tempX + tempZ*tempZ;
//				if(tempDist < a_radius*a_radius)
//					return true;
//
//			}
//		}
//	}
//	return false;
//}
//
//
//