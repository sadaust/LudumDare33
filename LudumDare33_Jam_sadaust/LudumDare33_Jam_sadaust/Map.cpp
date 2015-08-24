#include "Map.h"
#include <fstream>

void Map::loadMap(LPCSTR fName,int maxBuild,int maxCreatures,Building* buildings,Entity* creatures, ResourceManager* resMan) {
	std::ifstream file;
	file.open(fName);
	float left,right,back,front;
	float x,z,size;
	int curBuild, curCreatures;
	char lineType;

	curBuild = 0;
	curCreatures = 0;
	
	for(int i = 0; i < maxBuild; ++i) {
		buildings[i].setActive(false);
	}

	for(int i = 0; i < maxCreatures;++i) {
		creatures[i].setActive(false);
	}

	if(file.is_open()) {
		file>>left;
		file>>right;
		file>>back;
		file>>front;
		file.ignore();
		while(!file.eof()) {
			file>>lineType;
			if(lineType == 'b'||lineType == 'B') {
				file>>x;
				file>>z;
				file>>size;
				buildings[curBuild].setActive(true);
				buildings[curBuild].setPos(x,0,z);
				buildings[curBuild].setSize(size);
				++curBuild;
				if(curBuild>=maxBuild)
					curBuild = maxBuild-1;
			} else if(lineType == 'c'||lineType == 'C') {
				file>>x;
				file>>z;
				file>>size;
				creatures[curCreatures].setActive(true);
				creatures[curCreatures].setPos(x,0,z);
				creatures[curCreatures].setSize(size);
				++curCreatures;
				if(curCreatures>=maxCreatures)
					curCreatures = maxCreatures-1;
			}
			file.ignore();
		}
		playArea.back = back;
		playArea.front = front;
		playArea.left = left;
		playArea.right = right;
		playArea.top = 100;
		playArea.bottom = 0;
		ground.primInfo = resMan->loadPrim("ground",-1,0,left,right,front,back);
		D3DXMatrixIdentity(&ground.matrix);
		ground.Tex = resMan->loadTexture("ground.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
		file.close();
	}
}

RenInfo Map::getRen() {
	RenInfo info;
	info.type = primitive;
	info.locCamNum = 0;
	info.asset = &ground;
	return info;
}