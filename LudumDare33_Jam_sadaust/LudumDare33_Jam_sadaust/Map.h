#pragma once
#include "ResourceManager.h"
#include "Building.h"
#include "Entity.h"

class Map {
private:
	PrimObj ground;
	cube playArea;
public:
	void loadMap(LPCSTR file,int maxBuild,int maxCreatures,Building* buildings,Entity* creatures, ResourceManager* resMan);
	RenInfo getRen();
	cube getArea(){return playArea;}
	void setMat(D3DMATERIAL9* mat) {ground.mat = mat;}
};