#pragma once

#define num_Creatures 200
#define num_Buildings 100

#include "ResourceManager.h"
#include "InputHandler.h"
#include "SoundFrame.h"
#include "PhysicsSystem.h"
#include "Menu.h"
#include "Entity.h"
#include "Building.h"
#include "Map.h"

#include <sstream>

enum state {
	preGame,
	runGame,
	postGame
};

class Game{
private:
	ResourceManager resMan;
	DXFrame vidFram;
	SoundFrame sndFram;
	PhysicsSystem physSys;
	InputHandler input;
	inputState inState;
	cam camera;
	D3DLIGHT9 m_Light;
	DWORD cTime,lTime;
	double dt;

	D3DMATERIAL9 defMat;
	Entity player;
	Entity creatures[num_Creatures];
	Building buildings[num_Buildings];
	Map level;
	state gameState;
	double timeTaken;
	listenProp sndLis;
	SoundStruct* eat;
	TextStruct texOut;
	RenInfo texRen;
	std::string winMsg;

	float rotSpeed;
	float angSpeed;
	float angle;

	std::stringstream ss;

	/*
	//render test
	SpriteObj spriteTest;
	PrimObj primTest;
	RenInfo spriRen,primRen;
	*/
public:
	bool devLost();
	void resetDev(HWND& hWnd,HINSTANCE& hInsts);
	void init(HWND& hWnd, HINSTANCE& hInst,bool bWindowed);
	bool update();
	void draw();
	void shutDown();
	~Game(){shutDown();}
};