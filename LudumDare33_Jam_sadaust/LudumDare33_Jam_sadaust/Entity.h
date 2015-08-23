#pragma once
#include "ResourceManager.h"
#include "ShapeDefs.h"

class Entity {
private:
	D3DXVECTOR3 pos,lPos;
	D3DXVECTOR3 velocity;
	cylinder collisionInfo;
	float size;
	float rot;
	PrimObj m_prim;
	RenInfo m_render;
	bool active;
	bool eat;
public:
	Entity();
	RenInfo* getRender();
	void setRender(PrimObj &info);
	void update(double dt);
	void setCollision(float height, float width);
	void setSize(float a_size);
	void setPos(float x,float y,float z);
	void setVel(float x,float y,float z);
	void setEat(bool canEat);
	void setActive(bool isActive);
	void setRot(float a_rot);
	void rotate(float a_rot);
	void revPos();
	D3DXVECTOR3 getPos(){return pos;}
	cylinder getBound();
	float getRot() {return rot;}
	float getSize() {return size;}
	bool isActive(){return active;}
	bool canEat(){return eat;}
};