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

	//create light
	// Ambient light color emitted from this light
	m_Light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	// Diffuse light color emitted from this light
	m_Light.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	// Specular light color emitted from this light
	m_Light.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	// Light Type (Point) Requires: Position, Range, Attenuation
	m_Light.Type = D3DLIGHT_SPOT;	// Point, alternatively D3DLIGHT_DIRECTIONAL or D3DLIGHT_SPOT
	// Light Position
	m_Light.Position = D3DXVECTOR3(0.0f, 100.0f, 0.0f); 
	m_Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0);
	// Range of Light
	m_Light.Range = 1000.0f;
	// Light Attenuation
	m_Light.Attenuation0 = 0.0f;	// Constant
	m_Light.Attenuation1 = 0.05f;	// Linear
	m_Light.Attenuation2 = 0.0f;	// Quadratic
	//
	m_Light.Phi = D3DXToRadian(90.0f);
	m_Light.Theta = m_Light.Phi;
	// Set Light
	vidFram.setLight(0, &m_Light);
	//turn on light
	vidFram.setLightActive(0,true);

	//set default cam values
	camera.drawDist = 200.0f;
	camera.fov_deg = 90.f;
	camera.cam_pos.x = 0;
	camera.cam_pos.y = 0;
	camera.cam_pos.z = 0;
	camera.cam_look_pos.x = 0;
	camera.cam_look_pos.y = 0;
	camera.cam_look_pos.z = 0;
	camera.cam_up_vec.x = 0;
	camera.cam_up_vec.y = 1;
	camera.cam_up_vec.z = 0;
	vidFram.setCam(1,&camera);
	//set time
	cTime = timeGetTime();
	lTime = cTime;
	dt = 0;

	/*
	//render test
	//sprite test
	spriteTest.image = resMan.loadTexture("uvtest.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
	spriteTest.posX = 0.1f;
	spriteTest.posY = 0.1;
	spriteTest.scalX = 0.3f;
	spriteTest.scalY = 0.3f;
	spriRen.asset = &spriteTest.image;
	spriRen.locCamNum = 1;
	spriRen.type = sprite;
	//3d test
	testMat.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	testMat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Diffuse color reflected
	testMat.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Emissive color reflected
	testMat.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// Specular
	testMat.Power = 0.0f;
	primTest.mat = &testMat;
	primTest.Tex = resMan.loadTexture("uvtest.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
	primTest.primInfo = resMan.loadPrim("Cube",1.0f,1.0f,1.0f);
	D3DXMatrixIdentity(&primTest.matrix);
	primRen.asset = &primTest;
	primRen.locCamNum = 1;
	primRen.type = primitive;
	*/
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
		vidFram.clearRen();
		//update cam
		vidFram.setCam(1,&camera);

		vidFram.Render();
	}
}

void Game::shutDown() {
	input.shutdown();
	resMan.clear();
	sndFram.ShutDown();
	vidFram.Shutdown();
}