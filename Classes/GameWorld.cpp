#include "GameWorld.h"

#define WATERHEIGHT screenSize.height/3

GameWorld* GameWorld::m_singleton = NULL;

GameWorld::GameWorld(){
	m_world = new b2World(b2Vec2(NULL,NULL));
	m_world->SetContinuousPhysics(true);

	m_world->SetContactListener(&myListener);

	m_DebugDraw = new b2DebugDraw(PTM_RATIO );
		m_world->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
	m_DebugDraw->SetFlags(flags);
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("boatTest.plist");
	myListener.setWorld(m_world);
	b2Vec2 _waterPos(90.0f,WATERHEIGHT);
	b2Vec2 _waterSize(Globals::globalsInstance()->screenSize().width / PTM_RATIO,200.0f /PTM_RATIO);
	myListener.CreateWater(_waterPos,_waterSize,2.0f,2.0f);
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
	return playerBody;
}

void GameWorld::addObjects(){
	string _name = "PirateShip";

	playerSprite = CCSprite::create((_name+".png").c_str());

	playerSprite->setPosition(ccp(screenSize.width/2,WATERHEIGHT + playerSprite->getContentSize().height/4));

	mainLayer->addChild(playerSprite);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	
	bodyDef.position.Set(playerSprite->getPositionX()/PTM_RATIO,playerSprite->getPositionY()/PTM_RATIO);
	bodyDef.userData = playerSprite;
	playerBody = m_world->CreateBody(&bodyDef);

	GB2ShapeCache  *_shapeCache = GB2ShapeCache::sharedGB2ShapeCache();
	_shapeCache->addFixturesToBody(playerBody,_name.c_str());
	playerSprite->setAnchorPoint(_shapeCache->anchorPointForShape(_name.c_str()));
}