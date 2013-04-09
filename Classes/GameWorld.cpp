#include "GameWorld.h"

#define WATERHEIGHT screenSize.height/3

GameWorld* GameWorld::m_singleton = NULL;

GameWorld::GameWorld(){
	debugDrawBool = false;
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
	b2Vec2 lowerLeftCorner = b2Vec2(0, 0); 
	b2Vec2 lowerRightCorner = b2Vec2(widthInMeters, 0); 
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
	screenBorderShape.Set(lowerRightCorner, upperRightCorner); 
	groundBody->CreateFixture(&screenBorderShape, 0); 
	screenBorderShape.Set(upperRightCorner, upperLeftCorner); 
	groundBody->CreateFixture(&screenBorderShape, 0); 
	screenBorderShape.Set(upperLeftCorner, lowerLeftCorner); 
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
			CCSprite *objectData = (CCSprite *)b->GetUserData();
			objectData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
		    objectData->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));	
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
	return player->objBody;
}

void GameWorld::addObjects(){
	CCSprite* backgroundSprite = CCSprite::create("icebergback.png");
	backgroundSprite->setPosition(ccp(1024/2,768/1.51));
	//backgroundSprite->setScaleY(0.9f);
	backgroundSprite->setScaleX(1.0f);
	if(!debugDrawBool){
		mainLayer->addChild(backgroundSprite);
	}

	CCSprite* waterSprite2 = CCSprite::create("water.png");
	waterSprite2->setPosition(ccp(_waterPos.x,WATERHEIGHT/15));
	waterSprite2->setScaleY(0.9f);
	waterSprite2->setScaleX(2.0f);
	if(!debugDrawBool){
		mainLayer->addChild(waterSprite2);
	}

	player = new GameObject("Ship", screenSize.width/2,WATERHEIGHT + 10,1.0f);
	player->spriteInit(mainLayer);
	player->setObjPos(screenSize.width/2,WATERHEIGHT + player->objSprite->getContentSize().height/4);
	player->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ship.plist");

	enemy = new GameObject("Ship", screenSize.width/1.2,WATERHEIGHT + 10,1.0f);
	enemy->spriteInit(mainLayer);
	enemy->setObjPos(screenSize.width/2,WATERHEIGHT + enemy->objSprite->getContentSize().height/4);
	enemy->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ship.plist");

	submarine = new GameObject("Ship", screenSize.width/4,WATERHEIGHT + 10,1.0f);
	submarine->spriteInit(mainLayer);
	submarine->setObjPos(screenSize.width/2,WATERHEIGHT + submarine->objSprite->getContentSize().height/4);
	submarine->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ship.plist");

	CCSprite* waterSprite = CCSprite::create("waterAlpha.png");
	waterSprite->setPosition(ccp(_waterPos.x,WATERHEIGHT/15));
	waterSprite->setScaleY(0.9f);
	waterSprite->setScaleX(2.0f);
	mainLayer->addChild(waterSprite);
}

void GameWorld::shoot(){
	projectile = new GameObject("ball",submarine->objSprite->getPosition().x+50,submarine->objSprite->getPosition().y+50,1.0f);
	projectile->spriteInit(mainLayer);
	projectile->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ship.plist");
	projectile->objBody->ApplyLinearImpulse(b2Vec2(85.0f/PTM_RATIO,135.0f/PTM_RATIO),b2Vec2(submarine->objSprite->getPosition().x + 50,submarine->objSprite->getPosition().y + 50));
	
}

void GameWorld::debugVisuals(){
	if(debugDrawBool){
		debugDrawBool = false;
	} else {
		debugDrawBool = true;
	}
}