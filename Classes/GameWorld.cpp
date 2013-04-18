#include "GameWorld.h"
#include "GlassBox.h"

#define WATERHEIGHT screenSize.height/3

GameWorld* GameWorld::m_singleton = NULL;

GameWorld::GameWorld(){
	debugDrawBool = false;
	Globals::globalsInstance()->setUnitTurn(true);
	projectileFired = false;
	moving = false;
	shots = 0;
	m_world = new b2World(b2Vec2(NULL,NULL));
	m_world->SetContinuousPhysics(true);
	m_world->SetContactListener(&myListener);

	m_DebugDraw = new b2DebugDraw(PTM_RATIO);
		m_world->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		if(debugDrawBool){
			flags += b2Draw::e_shapeBit;
		}
	m_DebugDraw->SetFlags(flags);
	myListener.setWorld(m_world);
	_waterPos = b2Vec2((Globals::globalsInstance()->screenSize().width / 2),WATERHEIGHT);
	_waterSize = b2Vec2(Globals::globalsInstance()->screenSize().width / PTM_RATIO,(Globals::globalsInstance()->screenSize().height/3)/PTM_RATIO);
	myListener.CreateWater(_waterPos,_waterSize,1.0f,2.0f);
	srand(time(0));
	Globals::globalsInstance()->setWorld(m_world);
	Globals::globalsInstance()->setWaterheight(Globals::globalsInstance()->screenSize().height/3);
}

GameWorld* GameWorld::worldInstance(){
	if(NULL == m_singleton){
		m_singleton = new GameWorld();
	}
	return m_singleton;
}

void GameWorld::setBackground(const char* _location)
{
	CCSprite* bkgrd = CCSprite::create(_location);
	bkgrd->setPosition(ccp(screenSize.width/2, screenSize.height/2));
	mainLayer->addChild(bkgrd);
}

void GameWorld::createWorld(){
	addObjects();

	// Define the ground body.
	float widthInMeters = Globals::globalsInstance()->screenSize().width / PTM_RATIO; 
	float heightInMeters = Globals::globalsInstance()->screenSize().height / PTM_RATIO; 
	b2Vec2 lowerLeftCorner = b2Vec2(-widthInMeters, + hudBottom->getContentSize().height / PTM_RATIO); 
	b2Vec2 lowerRightCorner = b2Vec2(widthInMeters*2, + hudBottom->getContentSize().height / PTM_RATIO); 
	b2Vec2 upperLeftCorner = b2Vec2(0, heightInMeters); 
	b2Vec2 upperRightCorner = b2Vec2(widthInMeters, heightInMeters); 
		
	// Define the static container body, which will provide the collisions at screen borders. 
	b2BodyDef screenBorderDef; 
	b2Body* groundBody = m_world->CreateBody(&screenBorderDef);
	screenBorderDef.position.Set(0, 0); 
	groundBody = m_world->CreateBody(&screenBorderDef); 
	b2EdgeShape screenBorderShape; 

	// Create fixtures for the four borders (the border shape is re-used) 
	screenBorderShape.Set(lowerLeftCorner, lowerRightCorner); 
	groundBody->CreateFixture(&screenBorderShape, 0); 
	/*
	screenBorderShape.Set(b2Vec2(_waterSize.x,lowerRightCorner.y),b2Vec2(_waterSize.x,upperRightCorner.y));//lowerRightCorner, upperRightCorner); 
	groundBody->CreateFixture(&screenBorderShape, 0); 
	screenBorderShape.Set(upperRightCorner, upperLeftCorner); 
	groundBody->CreateFixture(&screenBorderShape, 0); 
	screenBorderShape.Set(b2Vec2(-_waterSize.x,lowerLeftCorner.y), b2Vec2(-_waterSize.x,upperLeftCorner.y));//lowerLeftCorner); 
	groundBody->CreateFixture(&screenBorderShape, 0);
	*/
	
}
b2World* GameWorld::getWorld(){
	return m_world;
}

void GameWorld::updateWorld(float dt){
	m_world->Step(dt,10,10);
	for(b2Body *b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if(b->GetUserData() != NULL)
		{
			CCSprite *objectData = (CCSprite*)b->GetUserData();
			objectData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
		    objectData->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));	
	    }
	}
	player->getWeaponBody(Ship::PLAYER)->SetTransform(b2Vec2(player->playerBody->GetPosition().x+player->playerSprite->getContentSize().width/player->getFactorX()/PTM_RATIO
		,player->playerBody->GetPosition().y+player->playerSprite->getContentSize().height/player->getFactorY()/PTM_RATIO),player->playerBody->GetAngle());
	enemy->getWeaponBody(Ship::ENEMY)->SetTransform(b2Vec2(enemy->enemyBody->GetPosition().x-enemy->enemySprite->getContentSize().width/enemy->getFactorX()/PTM_RATIO
		,enemy->enemyBody->GetPosition().y+enemy->enemySprite->getContentSize().height/enemy->getFactorY()/PTM_RATIO),enemy->enemyBody->GetAngle());
	myListener.update(dt);
	moving = false;

	//AI
	GlassBox::getGlassBox()->setAIOnBody(player->playerBody, enemy->enemyBody);
}

void GameWorld::setLayer(CCLayer* layer){
	mainLayer = layer;
	screenSize = Globals::globalsInstance()->screenSize();
}

void GameWorld::draw(void)
{
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    m_world->DrawDebugData();
    kmGLPopMatrix(); 
}

b2Body* GameWorld::getPlayer(){
	return player->playerBody;
}

void GameWorld::addObjects(){
	addArt();
	player = new Ship(Ship::SHIP, Ship::PLAYER, WATERHEIGHT, mainLayer, m_world);
	enemy = new Ship(Ship::SHIP, Ship::ENEMY, WATERHEIGHT, mainLayer, m_world);
}

void GameWorld::shootAI()
{
	moving = false;

	if (!Globals::globalsInstance()->getUnitTurn()){
		if(enemy->getEnemyType() == Ship::SHIP){
			//proj = new Projectile(Projectile::PROJ_CANNONBALL,b2Vec2(enemy->enemySprite->getPositionX(),enemy->enemySprite->getPositionY()),mainLayer,m_world, -1,enemy->enemyBody->GetAngle());
			proj = new Projectile(Projectile::PROJ_CANNONBALL,b2Vec2(enemy->getWeaponBody(Ship::ENEMY)->GetPosition().x*32,enemy->getWeaponBody(Ship::ENEMY)->GetPosition().y*32)
				,mainLayer,m_world, -1,enemy->getWeaponBody(Ship::ENEMY)->GetAngle() * rand());
			enemy->enemyBody->ApplyForceToCenter(b2Vec2(5,-25));
		} else if (enemy->getEnemyType() == Ship::SUBMARINE){
			//proj = new Projectile(Projectile::PROJ_TORPEDO,b2Vec2(enemy->enemySprite->getPositionX(),enemy->enemySprite->getPositionY()),mainLayer,m_world, -1,enemy->enemyBody->GetAngle());
			proj = new Projectile(Projectile::PROJ_TORPEDO,b2Vec2(enemy->getWeaponBody(Ship::ENEMY)->GetPosition().x*32,enemy->getWeaponBody(Ship::ENEMY)->GetPosition().y*32)
				,mainLayer,m_world, -1,enemy->getWeaponBody(Ship::ENEMY)->GetAngle() * rand());
			enemy->enemyBody->ApplyForceToCenter(b2Vec2(15,0));
		}
		//enemy->getWeaponBody(Ship::ENEMY)->SetTransform(enemy->enemyBody->GetPosition(),enemy->enemyBody->GetAngle());
		Globals::globalsInstance()->setUnitTurn(true);
	}
}

void GameWorld::shoot(){
	moving = false;
	if(Globals::globalsInstance()->getUnitTurn()){
		if(player->getPlayerType() == Ship::SHIP){
			//proj = new Projectile(Projectile::PROJ_CANNONBALL,b2Vec2(player->playerSprite->getPositionX(),player->playerSprite->getPositionY()),mainLayer,m_world, 1,player->playerBody->GetAngle());
			proj = new Projectile(Projectile::PROJ_CANNONBALL,b2Vec2(player->getWeaponBody(Ship::PLAYER)->GetPosition().x*32,player->getWeaponBody(Ship::PLAYER)->GetPosition().y*32)
				,mainLayer,m_world, 1,player->getWeaponBody(Ship::PLAYER)->GetAngle());
			player->playerBody->ApplyForceToCenter(b2Vec2(-5,-25));
		} else if (player->getPlayerType() == Ship::SUBMARINE){
			//proj = new Projectile(Projectile::PROJ_TORPEDO,b2Vec2(player->playerSprite->getPositionX(),player->playerSprite->getPositionY()),mainLayer,m_world, 1,player->playerBody->GetAngle());
			proj = new Projectile(Projectile::PROJ_TORPEDO,b2Vec2(player->getWeaponBody(Ship::PLAYER)->GetPosition().x*32,player->getWeaponBody(Ship::PLAYER)->GetPosition().y*32)
				,mainLayer,m_world, 1,player->getWeaponBody(Ship::PLAYER)->GetAngle());
			player->playerBody->ApplyForceToCenter(b2Vec2(-15,0));
		}
		//player->getWeaponBody(Ship::PLAYER)->SetTransform(player->playerBody->GetPosition(),player->playerBody->GetAngle());
		Globals::globalsInstance()->setUnitTurn(false);
	}
}

void GameWorld::moveShip(){
	moving = true;
	if(Globals::globalsInstance()->getUnitTurn()){
		if(player->getPlayerType() == Ship::SHIP){
			player->playerBody->ApplyForceToCenter(b2Vec2(25.0,0.0));
		} else if (player->getPlayerType() == Ship::SUBMARINE){
			player->playerBody->ApplyForceToCenter(b2Vec2(50.0,0.0));
			player->playerBody->SetFixedRotation(moving);
		}
		Globals::globalsInstance()->setUnitTurn(false);
	} else if (!Globals::globalsInstance()->getUnitTurn()){
		if(enemy->getEnemyType() == Ship::SHIP){
			enemy->enemyBody->ApplyForceToCenter(b2Vec2(-25.0,0.0));
		} else if (enemy->getEnemyType() == Ship::SUBMARINE){
			enemy->enemyBody->ApplyForceToCenter(b2Vec2(-50.0,0.0));
			player->playerBody->SetFixedRotation(moving);
		}
		Globals::globalsInstance()->setUnitTurn(true);
	}
	//Globals::globalsInstance()->Output(Globals::globalsInstance()->getPlayerHealth());
	//Globals::globalsInstance()->Output(Globals::globalsInstance()->getEnemyHealth());
}

void GameWorld::debugVisuals(){
	if(debugDrawBool){
		debugDrawBool = false;
	} else {
		debugDrawBool = true;
	}
}

void GameWorld::addArt(){
	backgroundSprite = CCSprite::create("icebergback.png");
	backgroundSprite->setPosition(ccp(Globals::globalsInstance()->screenSize().width/2,Globals::globalsInstance()->screenSize().height/1.51));
	backgroundSprite->setScaleX(1.0f);
	backgroundSprite->_setZOrder(GameObject::BACKGROUND);
	if(!debugDrawBool){
		mainLayer->addChild(backgroundSprite);
	}

	waterSprite = CCSprite::create("water4.png",CCRect(0,0,_waterSize.x*(PTM_RATIO*2),_waterSize.y*(PTM_RATIO)));
	waterSprite->setPosition(ccp(_waterPos.x,WATERHEIGHT/2));
	waterSprite->_setZOrder(GameObject::BACKGROUND);
	if(!debugDrawBool){
		mainLayer->addChild(waterSprite);
	}

	waterAlphaSprite = CCSprite::create("waterAlpha3.png",CCRect(0,0,_waterSize.x*(PTM_RATIO*2),_waterSize.y*(PTM_RATIO)));
	waterAlphaSprite->setPosition(ccp(_waterPos.x,WATERHEIGHT/2));
	waterAlphaSprite->_setZOrder(GameObject::FOREGROUND);
	mainLayer->addChild(waterAlphaSprite);

	hudBottom = CCSprite::create("hud.png");
	hudBottom->setPosition(ccp(Globals::globalsInstance()->screenSize().width/2,hudBottom->getContentSize().height/2));
	hudBottom->_setZOrder(GameObject::HUD);
	mainLayer->addChild(hudBottom);

	hudTop = CCSprite::create("hud.png");
	hudTop->setPosition(ccp(Globals::globalsInstance()->screenSize().width/2,Globals::globalsInstance()->screenSize().height - hudTop->getContentSize().height/2));
	hudTop->_setZOrder(GameObject::HUD);
	hudTop->setFlipY(true);
	mainLayer->addChild(hudTop);
}