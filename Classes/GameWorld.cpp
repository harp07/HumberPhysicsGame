#include "GameWorld.h"

#define PTM_RATIO 32.0

GameWorld* GameWorld::m_singleton = NULL;

GameWorld::GameWorld(){
	m_world = new b2World(b2Vec2(NULL,NULL));
	m_world->SetContinuousPhysics(true);
}

GameWorld* GameWorld::worldInstance(){
	if(NULL == m_singleton){
		m_singleton = new GameWorld();
	}
	return m_singleton;
}

void GameWorld::setBackground(const char* _img1, const char* _img2)
{
	CCSprite* bkgrd = CCSprite::create(_img1);
	bkgrd->setPosition(ccp(screenSize.width/2, screenSize.height/2));
	//mainLayer->addChild(bkgrd);
	bkgrd->setAnchorPoint( ccp(0,0));

	CCSprite* bkgrd2 = CCSprite::create(_img2);
	bkgrd2->setAnchorPoint( ccp(0,0));

	//Parallax not working yet
	//CCParallaxNode* bkgrdNode = CCParallaxNode::create();
	//bkgrdNode->addChild(bkgrd, -1, 1);
	//bkgrdNode->addChild(bkgrd2, -1, 2);
	//mainLayer->addChild(bkgrdNode);	
}

void GameWorld::setParallax()
{

}

void GameWorld::createWorld(){
	CCSprite *sprite = CCSprite::create("CloseNormal.png",CCRectMake(0,0,40,40));
	sprite->setScale(0.4f);
	sprite->setPosition(ccp((screenSize.width/4)/PTM_RATIO,(screenSize.height/2)/PTM_RATIO));
	mainLayer->addChild(sprite);

	b2Body *_sphere;
	b2BodyDef sphereDef;
	sphereDef.type = b2_dynamicBody;
	sphereDef.position.Set(sprite->getPositionX(),sprite->getPositionY());
	sphereDef.userData = sprite;
	_sphere = m_world->CreateBody(&sphereDef);
	b2CircleShape sphereShape;

	sphereShape.m_radius = 10.0f /PTM_RATIO;
	b2FixtureDef sphereFix;
	sphereFix.shape = &sphereShape;
	sphereFix.restitution = 1.0f;
	sphereFix.density = 20.0f;
	_sphere->CreateFixture(&sphereFix);

	b2Body *_box;
	b2BodyDef boxDef;

	boxDef.type = b2_dynamicBody;
	boxDef.position.Set(350.0f / PTM_RATIO,300.0f / PTM_RATIO);
	_box       = m_world->CreateBody(&boxDef);
	b2PolygonShape boxShape;

	boxShape.SetAsBox(10  / PTM_RATIO, 10 / PTM_RATIO);
	b2FixtureDef boxFix;
	boxFix.shape = &boxShape;
	boxFix.density = 10.0f;
	boxFix.restitution = 1.0f;
	_box->CreateFixture(&boxFix);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(screenSize.width/2/PTM_RATIO, screenSize.height/2/PTM_RATIO); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;
    // bottom
    groundBox.SetAsBox(screenSize.width/2/PTM_RATIO, 0, b2Vec2(0, -screenSize.height/2/PTM_RATIO), 0);
 	groundBody->CreateFixture(&groundBox, 0);
	
    // top
    groundBox.SetAsBox(screenSize.width/2/PTM_RATIO, 0, b2Vec2(0, screenSize.height/2/PTM_RATIO), 0);
    groundBody->CreateFixture(&groundBox, 0);

    // left
    groundBox.SetAsBox(0, screenSize.height/2/PTM_RATIO, b2Vec2(-screenSize.width/2/PTM_RATIO, 0), 0);
    groundBody->CreateFixture(&groundBox, 0);

    // right
    groundBox.SetAsBox(0, screenSize.height/2/PTM_RATIO, b2Vec2(screenSize.width/2/PTM_RATIO, 0), 0);
    groundBody->CreateFixture(&groundBox, 0);
}
b2World* GameWorld::getWorld(){
	return m_world;
}

void GameWorld::setLayer(CCLayer* layer,CCSize winSize){
	mainLayer = layer;
	screenSize = winSize;
}

void GameWorld::draw(){
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    m_world->DrawDebugData();
    kmGLPopMatrix();
}