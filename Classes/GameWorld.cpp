#include "GameWorld.h"

#define WATERHEIGHT screenSize.height/3

GameWorld* GameWorld::m_singleton = NULL;

GameWorld::GameWorld(){
	debugDrawBool = false;
	projectileFired = false;
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
		if(projectileFired){
			//b->ApplyForceToCenter(b2Vec2(-10.0f/PTM_RATIO,0.0f));
		}
	}
	myListener.update(dt);
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
	player = new Ship(Ship::SUBMARINE, Ship::PLAYER, WATERHEIGHT, mainLayer, m_world);
	enemy = new Ship(Ship::SHIP, Ship::ENEMY, WATERHEIGHT, mainLayer, m_world);
}

void GameWorld::shoot(){
	if(shots == 0){
		if(player->getPlayerType() == Ship::SHIP){
			proj = new Projectile(Projectile::PROJ_CANNONBALL,b2Vec2(player->playerSprite->getPositionX(),player->playerSprite->getPositionY()),mainLayer,m_world, 1);
		} else if (player->getPlayerType() == Ship::SUBMARINE){
			proj = new Projectile(Projectile::PROJ_TORPEDO,b2Vec2(player->playerSprite->getPositionX(),player->playerSprite->getPositionY()),mainLayer,m_world, 1);
		}
		shots = 1;
	}
	else if (shots == 1){
		if(enemy->getEnemyType() == Ship::SHIP){
			proj = new Projectile(Projectile::PROJ_CANNONBALL,b2Vec2(enemy->enemySprite->getPositionX(),enemy->enemySprite->getPositionY()),mainLayer,m_world, -1);
		} else if (enemy->getEnemyType() == Ship::SUBMARINE){
			proj = new Projectile(Projectile::PROJ_TORPEDO,b2Vec2(enemy->enemySprite->getPositionX(),enemy->enemySprite->getPositionY()),mainLayer,m_world, -1);
		}
		shots = 0;
	}
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