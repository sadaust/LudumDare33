#pragma once

#include "ResourceManager.h"
#include "ShapeDefs.h"

class Building {
private:
	D3DXVECTOR3 pos;
	cube colInfo;
	float size;
	PrimObj m_prim;
	RenInfo m_render;
	bool active;
public:
	Building();
	RenInfo* getRender();
	void setRender(PrimObj &info);
	void setCollision(float left,float right,float back,float front,float top,float bottom);
	cube getCol();
	void setPos(float x,float y,float z){pos.x = x;pos.y = y;pos.z = z;}
	void setSize(float a_size){size = a_size;}
	D3DXVECTOR3 getPos(){return pos;}
	float getSize(){return size;}
	void setActive(bool isActive){active = isActive;}
	bool isActive(){return active;}
};