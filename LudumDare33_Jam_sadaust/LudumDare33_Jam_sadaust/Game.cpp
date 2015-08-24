#include "Game.h"
#include <ctime>

void rotate2Dvector(D3DXVECTOR2* a_vector, float a_angle) {
	float Y = sinf(a_angle) * a_vector->x + cosf(a_angle) * a_vector->y;
	float X = cosf(a_angle) * a_vector->x - sinf(a_angle) * a_vector->y;
	a_vector->x = X;
	a_vector->y = Y;
}

void Game::init(HWND& hWnd, HINSTANCE& hInst,bool bWindowed) {
	gameState = preGame;
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
	temp.Tex = resMan.loadTexture("player.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
	temp.mat = &defMat;

	player.setRender(temp);
	player.setActive(true);
	player.setEat(true);
	player.setCollision(1,1);
	player.setSize(1);
	angle = 0;

	timeTaken = 0;

	//load creature assets
	temp.primInfo = resMan.loadPrim("creature",0,1,-0.5f,0.5f,0.5f,-0.5f);
	temp.Tex = resMan.loadTexture("enemy.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
	temp.mat = &defMat;
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
	temp.Tex = resMan.loadTexture("building.png",0,0,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,D3DCOLOR_XRGB(255,0,255),0);
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
	rotSpeed = 0.45f;
	angSpeed = 0.15f;

	level.setMat(&defMat);
	level.loadMap("map.txt",num_Buildings,num_Creatures,buildings,creatures,&resMan);

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
	sndLis.up.x = 0;
	sndLis.up.y = 1;
	sndLis.up.z = 0;
	eat = resMan.loadSound("eat.wav",100,1000,1);
	sndFram.setNumListen(1);
	sndFram.setListenProp(1,sndLis);
	texOut.textColor = D3DCOLOR(0xFFFFFFFF);
	texOut.text = "Use WASD to move Mouse to move camera, left click to start";
	texOut.rec.left = 0.5;
	texOut.rec.top = 0.5;
	texOut.rec.right = 0.5;
	texOut.rec.bottom = 0.5;
	texRen.asset = &texOut;
	texRen.locCamNum = 1;
	texRen.type = text;
}

bool Game::devLost() {
	return vidFram.rendererLost();
}

void Game::resetDev(HWND& hWnd,HINSTANCE& hInsts) {
	vidFram.resetDev(hWnd,hInsts);
	resMan.reloadVideo();
}

bool Game::update() {
	bool win;
	D3DXVECTOR2 temp;
	//get delta time
	win = true;
	cTime = timeGetTime();
	dt = (float)(cTime-lTime);
	dt /= CLOCKS_PER_SEC;
	lTime = cTime;
	//update game engine
	input.update();
	sndFram.update();
	//update game state
	if(gameState == preGame) {
		input.getState(4,inState);
		if(inState.buttons[binds::leftAttack]) {
			texOut.rec.left = 0.5;
			texOut.rec.top = 0.0;
			texOut.rec.right = 0.5;
			texOut.rec.bottom = 0.5;
			gameState = runGame;
		}
	} else if(gameState == runGame) {
		//player input
		input.getState(4,inState);
		temp.x = inState.lX;
		temp.y = inState.lY;
		player.rotate((inState.rX)*rotSpeed);
		angle -= (inState.rY)*angSpeed;
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
		//make sure player is still in play area
		if(player.getPos().x>level.getArea().front||player.getPos().x<level.getArea().back||player.getPos().z>level.getArea().right||player.getPos().z<level.getArea().left)
			player.revPos();
		//do collision
		for(int i = 0; i < num_Creatures; ++i) {
			if(creatures[i].isActive()) {
				if(physSys.SenseCollision(player,creatures[i])) {
					if(physSys.ResolveCollision(player,creatures[i]))
						sndFram.Play(*eat,player.getPos().x,player.getPos().y,player.getPos().z,0,0,0);
				}
				win = false;
			}
		}
		for(int i = 0; i < num_Buildings; ++i) {
			if(buildings[i].isActive()) {
				if(physSys.SenseCollision(player,buildings[i])) {
					if(physSys.ResolveCollision(player,buildings[i]))
						sndFram.Play(*eat,player.getPos().x,player.getPos().y,player.getPos().z,0,0,0);
				}
				win = false;
			}
		}
		sndLis.pos.x = player.getPos().x;
		sndLis.pos.y = player.getPos().y;
		sndLis.pos.z = player.getPos().z;
		sndLis.vel.x = 0;
		sndLis.vel.y = 0;
		sndLis.vel.z = 0;
		sndFram.setListenProp(1,sndLis);
		timeTaken += dt;
		ss.str("");
		ss<<"Time: "<<(int)timeTaken<<"\n";
		winMsg = ss.str();
		texOut.text = winMsg;
		if(win) {
			texOut.rec.left = 0.5;
			texOut.rec.top = 0.5;
			texOut.rec.right = 0.5;
			texOut.rec.bottom = 0.5;
			timeTaken = (int)timeTaken;
			ss.str("");
			ss<<"YOU WIN! It took "<<timeTaken<<" seconds. Left Click to restart\n";
			winMsg = ss.str();
			texOut.text = winMsg;
			gameState = postGame;
		}
	} else if(gameState == postGame) {
		input.getState(4,inState);
		if(inState.buttons[binds::leftAttack]) {
			player.setPos(0,0,0);
			player.setRot(0);
			player.setSize(1);
			level.loadMap("map.txt",num_Buildings,num_Creatures,buildings,creatures,&resMan);
			texOut.rec.left = 0.5;
			texOut.rec.top = 0.0;
			texOut.rec.right = 0.5;
			texOut.rec.bottom = 0.5;
			timeTaken = 0;
			gameState = runGame;
		}
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
		vidFram.addRen(texRen);
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
		vidFram.addRen(level.getRen());

		vidFram.Render();
	}
}

void Game::shutDown() {
	input.shutdown();
	resMan.clear();
	sndFram.ShutDown();
	vidFram.Shutdown();
}