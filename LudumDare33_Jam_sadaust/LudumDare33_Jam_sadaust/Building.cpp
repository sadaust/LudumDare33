#include "Building.h"

Building::Building() {
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	size = 100;
	active = false;
}

void Building::setRender(PrimObj &info) {
	m_prim.mat = info.mat;
	m_prim.primInfo = info.primInfo;
	m_prim.Tex = info.Tex;
	D3DXMatrixIdentity(&m_prim.matrix);
	
	m_render.asset = &m_prim;
	m_render.locCamNum = 0;
	m_render.type = primitive;
}

RenInfo* Building::getRender() {
	D3DXMATRIX TransMat, posMat, scaleMat;
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&posMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixScaling(&scaleMat,size,1,size);
	D3DXMatrixTranslation(&posMat,pos.x,pos.y,pos.z);
	D3DXMatrixMultiply(&TransMat,&scaleMat,&posMat);
	m_prim.matrix = TransMat;
	return &m_render;
}

void Building::setSize(float a_size) {
	size = a_size;
	//update colision
	colInfo.back = baseCol.back*size;
	colInfo.front = baseCol.front*size;
	colInfo.left = baseCol.left*size;
	colInfo.right = baseCol.right*size;
	colInfo.top = baseCol.top;
	colInfo.bottom = baseCol.bottom;
}

void Building::setCollision(float left,float right,float back,float front,float top,float bottom) {
	baseCol.back = back;
	baseCol.front = front;
	baseCol.left = left;
	baseCol.right = right;
	baseCol.top = top;
	baseCol.bottom = bottom;

	colInfo.back = back*size;
	colInfo.front = front*size;
	colInfo.left = left*size;
	colInfo.right = right*size;
	colInfo.top = top;
	colInfo.bottom = bottom;
}

cube Building::getCol() {
	return colInfo;
}