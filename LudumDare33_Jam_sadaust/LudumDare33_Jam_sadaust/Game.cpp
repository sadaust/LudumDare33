#include "Game.h"
#include <ctime>

void rotate2Dvector(D3DXVECTOR2* a_vector, float a_angle) {
	float Y = sinf(a_angle) * a_vector->x + cosf(a_angle) * a_vector->y;
	float X = cosf(a_angle) * a_vector->x - sinf(a_angle) * a_vector->y;
	a_vector->x = X;
	a_vector->y = Y;
}

void Game::init(HWND& hWnd, HINSTANCE& hInst,bool bWindowed) {
	PrimObj temp;
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
	camera.drawDist = 20000.0f;
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

	//creat default material
	defMat.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	defMat.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		// Diffuse color reflected
	defMat.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// Emissive color reflected
	defMat.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// Specular
	defMat.Power = 0.0f;
	//load player assets
	temp.primInfo = resMan.loadPrim("Player",0,1,-0.5f,0.5f,0.5f,-0.5f);
	temp.Tex = resMan.loadTexture("uvtest.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
	temp.mat = &defMat;

	player.setRender(temp);
	player.setActive(true);
	player.setEat(true);
	player.setCollision(1,1);
	player.setSize(1);
	angle = 0;

	//setup creatures
	for(int i = 0; i < num_Creatures; ++i) {
		creatures[i].setActive(true);
		creatures[i].setPos((5*i)+5,0,0);
		creatures[i].setRender(temp);
		creatures[i].setCollision(1,0.25f);
		creatures[i].setSize(i+1);
	}
	//load building assets
	temp.primInfo = resMan.loadPrim("Building",0,50.0f,-1.0f,1.0f,1.0f,-1.0f);
	temp.Tex = resMan.loadTexture("uvtest.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
	temp.mat = &defMat;
	//setup buildings
	for(int i = 0; i < num_Buildings; ++i) {
		buildings[i].setSize(10*i);
		buildings[i].setActive(true);
		buildings[i].setRender(temp);
		buildings[i].setCollision(-1.0f,1.0f,-1.0f,1.0,50,0);
		buildings[i].setPos(0,0,(100*i)+100);
	}
	//set input
	rotSpeed = 90;
	angSpeed = 45;

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
	primTest.mat = &defMat;
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
	D3DXVECTOR2 temp;
	//get delta time
	cTime = timeGetTime();
	dt = (float)(cTime-lTime);
	dt /= CLOCKS_PER_SEC;
	lTime = cTime;
	//update game engine
	input.update();
	sndFram.update();
	//update game state
	//player input
	input.getState(4,inState);
	temp.x = inState.lX;
	temp.y = inState.lY;
	player.rotate((inState.rX*dt)*rotSpeed);
	angle -= (inState.rY*dt)*angSpeed;
	if(angle >= 90)
		angle = 89.9f;
	else if(angle <=-90)
		angle = -89.9f;
	rotate2Dvector(&temp,D3DXToRadian(-player.getRot()));
	player.setVel(temp.x,0,temp.y);
	//update player
	player.update(dt);
	//update creatures
	for(int i = 0; i < num_Creatures; ++i) {
		creatures[i].update(dt);
	}
	//do collision
	for(int i = 0; i < num_Creatures; ++i) {
		if(creatures[i].isActive())
			if(physSys.SenseCollision(player,creatures[i]))
				physSys.ResolveCollision(player,creatures[i]);
	}
	for(int i = 0; i < num_Buildings; ++i) {
		if(buildings[i].isActive())
			if(physSys.SenseCollision(player,buildings[i]))
				physSys.ResolveCollision(player,buildings[i]);
	}
	//render
	draw();
	return true;
}

void Game::draw() {
	if(!vidFram.rendererLost()) {
		vidFram.clearRen();
		//update cam
		camera.cam_look_pos.x = player.getPos().x;
		camera.cam_look_pos.z = player.getPos().z;
		camera.cam_look_pos.y = 1*player.getSize();
		vidFram.rotateCam(camera,player.getSize()*2.0f,player.getRot(),angle);
		vidFram.setCam(1,&camera);
		//render
		if(player.isActive())
			vidFram.addRen(*player.getRender());
		for(int i = 0; i < num_Creatures; ++i) {
			if(creatures[i].isActive()) {
				vidFram.addRen(*creatures[i].getRender());
			}
		}
		for(int i = 0; i < num_Buildings; ++i) {
			if(buildings[i].isActive()) {
				vidFram.addRen(*buildings[i].getRender());
			}
		}
		vidFram.Render();
	}
}

void Game::shutDown() {
	input.shutdown();
	resMan.clear();
	sndFram.ShutDown();
	vidFram.Shutdown();
}