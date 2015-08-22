#pragma once

#include "ResourceManager.h"
#include "InputHandler.h"
#include "SoundFrame.h"
//#include "PhysicsSystem.h"
#include "Menu.h"

class Game{
private:
	ResourceManager resMan;
	DXFrame vidFram;
	SoundFrame sndFram;
	//PhysicsSystem physSys;
	InputHandler input;
	cam camera;
	D3DLIGHT9 m_Light;
	DWORD cTime,lTime;
	double dt;

	//render test
	SpriteObj spriteTest;
	PrimObj primTest;
	D3DMATERIAL9 testMat;
	RenInfo spriRen,primRen;

public:
	bool devLost();
	void resetDev(HWND& hWnd,HINSTANCE& hInsts);
	void init(HWND& hWnd, HINSTANCE& hInst,bool bWindowed);
	bool update();
	void draw();
	void shutDown();
	~Game(){shutDown();}
};