#include "Entity.h"

Entity::Entity() {
	setPos(0,0,0);
	setVel(0,0,0);
	setActive(false);
	setSize(1);
	speed = 1;
	setRot(0);
	setEat(false);
}

RenInfo* Entity::getRender() {
	D3DXMATRIX TransMat, RotMat, posMat, scaleMat;
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&RotMat);
	D3DXMatrixIdentity(&posMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixScaling(&scaleMat,size,size,size);
	D3DXMatrixRotationY(&RotMat,D3DXToRadian(rot));
	D3DXMatrixTranslation(&posMat,pos.x,pos.y,pos.z);
	D3DXMatrixMultiply(&TransMat,&scaleMat,&RotMat);
	D3DXMatrixMultiply(&TransMat,&TransMat,&posMat);
	m_prim.matrix = TransMat;
	return &m_render;
}

void Entity::setRender(PrimObj &info) {
	m_prim.mat = info.mat;
	m_prim.primInfo = info.primInfo;
	m_prim.Tex = info.Tex;
	D3DXMatrixIdentity(&m_prim.matrix);
	
	m_render.asset = &m_prim;
	m_render.locCamNum = 0;
	m_render.type = primitive;
}

void Entity::revPos() {
	pos = lPos;
}

void Entity::update(double dt) {
	if(active) {
		lPos = pos;
		pos += velocity*dt*speed*size;
		/*pos.x += velocity.x*dt;
		pos.y += velocity.y*dt;
		pos.z += velocity.z*dt;*/
	}
}

void Entity::setCollision(float height, float width) {
	baseCol.height = height;
	baseCol.radius = width;
	collisionInfo.height = height * size;
	collisionInfo.radius = width * size;
}

void Entity::setSize(float a_size) {
	size = a_size;
	collisionInfo.height = baseCol.height*size;
	collisionInfo.radius = baseCol.radius*size;
}

void Entity::setPos(float x,float y,float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Entity::rotate(float a_rot) {
	rot += a_rot;
}

void Entity::setRot(float a_rot) {
	rot = a_rot;
}

void Entity::setVel(float x,float y,float z) {
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Entity::setEat(bool canEat) {
	eat = canEat;
}

void Entity::setActive(bool isActive) {
	active = isActive;
}

cylinder Entity::getBound() {
	/*cylinder temp;
	temp = collisionInfo;
	temp.height *= size;
	temp.radius *= size;
	return temp;*/
	return collisionInfo;
}