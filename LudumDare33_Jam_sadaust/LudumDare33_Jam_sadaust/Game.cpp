#include "Game.h"
#include <ctime>

void Game::init(HWND& hWnd, HINSTANCE& hInst,bool bWindowed) {
	//start Direct X
	vidFram.init(hWnd,hInst,bWindowed);
	vidFram.setViewCount(1);
	vidFram.setCam(1,&camera);
	//start FMOD
	sndFram.Init();
	//start input
	input.init(hWnd,hInst);
	//start resMan
	resMan.changeDevice(&vidFram);
	resMan.changeDevice(&sndFram);
	//set
	cTime = timeGetTime();
	lTime = cTime;
	dt = 0;
}

bool Game::devLost() {
	return vidFram.rendererLost();
}

void Game::resetDev(HWND& hWnd,HINSTANCE& hInsts) {
	vidFram.resetDev(hWnd,hInsts);
	resMan.reloadVideo();
}

bool Game::update() {
	//get delta time
	cTime = timeGetTime();
	dt = (float)(cTime-lTime);
	dt /= CLOCKS_PER_SEC;
	lTime = cTime;
	//update game engine
	input.update();
	sndFram.update();
	//render
	draw();
	return true;
}

void Game::draw() {
	if(!vidFram.rendererLost()) {
		//vidFram.clearRen();

		vidFram.Render();
	}
}

void Game::shutDown() {
	input.shutdown();
	resMan.clear();
	sndFram.ShutDown();
	vidFram.Shutdown();
}