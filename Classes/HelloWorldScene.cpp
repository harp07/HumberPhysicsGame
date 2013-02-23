#include "HelloWorldScene.h"

#define PTM_RATIO 32.0

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
	{
		
        CC_BREAK_IF(! CCLayer::init());

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

		gravity = b2Vec2(0.0f,-9.8f);
		m_world = new b2World(gravity);
		m_world->SetContinuousPhysics(true);

		///////////////////////////////////////////////////////////////////////////////////
		//For Box2d Debug Drawing//
		m_DebugDraw = new b2DebugDraw(PTM_RATIO);
		m_world->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		m_DebugDraw->SetFlags(flags);

		//////////////////////////////////////////////////////////////////////////////////

		this->ground();
		
		b2BodyDef sphereDef;

		sphereDef.type = b2_dynamicBody;
		sphereDef.position.Set(90.0f/PTM_RATIO,200.0f/PTM_RATIO);
		_sphere    = m_world->CreateBody(&sphereDef);
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

		//schedule(schedule_selector(HelloWorld::update),1/60);
		scheduleUpdate();
        bRet = true;
		Camera::cameraInstance()->setLayer(this);
		this->setTouchEnabled(true);
    } while (0);

    return bRet;
}

void HelloWorld::update(float dt)
{
	int32 velocityIterations = 10;
	int32 positionIterations = 10;
	m_world->Step(dt,velocityIterations,positionIterations);
	m_world->ClearForces();
}

void HelloWorld::ccTouchesBegan(CCSet *touches, CCEvent* event){
	Camera::cameraInstance()->setFocus(ccp(_sphere->GetPosition().x/PTM_RATIO,_sphere->GetPosition().y/PTM_RATIO));
}

void HelloWorld::ccTouchesMoved(CCSet *touches, CCEvent* event){
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	Camera::cameraInstance()->moveCamera(ccp(location.x/PTM_RATIO,0.0f));
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event){
	Camera::cameraInstance()->reset();
}

void HelloWorld::draw(void)
{
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    m_world->DrawDebugData();
    kmGLPopMatrix(); 
}

void HelloWorld::ground(){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
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