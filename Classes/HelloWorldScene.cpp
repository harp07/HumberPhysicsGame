#include "HelloWorldScene.h"
#include <stdio.h>
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

void HelloWorld::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	kick();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
	{
        CC_BREAK_IF(! CCLayer::init());

		 screenSize = CCDirector::sharedDirector()->getWinSize();


		 this->setTouchEnabled(false);

		 box = CCSprite::create("wooden_box.jpg");
		 CC_BREAK_IF(! box);

		 ball = CCSprite::create("Rock-01.png");
		 CC_BREAK_IF(! ball);
		initPhysics();
		scheduleUpdate();



		box->setScale(0.09);

		ball->setScale(1.0);

		addChild(box,0);
		addChild(ball,0);

		///////////////////////////////////////////////////////////////////////////////////
		//For Box2d Debug Drawing//
		m_DebugDraw = new b2DebugDraw(PTM_RATIO);
		m_world->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		
		m_DebugDraw->SetFlags(flags);
		
		
		//////////////////////////////////////////////////////////////////////////////////
        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::kick()
{
	b2Vec2 force = b2Vec2(30,30);
	_sphere->ApplyLinearImpulse(force,_sphere->GetPosition());

}
void HelloWorld::update(float dt)
{
	m_world->Step(dt,10,10);
	for(b2Body *b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if(b->GetUserData() != NULL)
		{
			CCSprite *ballData = (CCSprite *)b->GetUserData();
			ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
			ballData->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));

			
	  }
	
	}

	
}
void HelloWorld::initPhysics()
{
gravity = b2Vec2(0.0f,-9.8f);
		m_world = new b2World(gravity);
		m_world->SetContinuousPhysics(true);
		
	

	sphereDef.type = b2_dynamicBody;
	sphereDef.userData = ball;
	sphereDef.position.Set(90.0f/PTM_RATIO,200.0f/PTM_RATIO);
	_sphere    = m_world->CreateBody(&sphereDef);
	b2CircleShape sphereShape;

	sphereShape.m_radius = 10.0f /PTM_RATIO;
	b2FixtureDef sphereFix;
	sphereFix.shape = &sphereShape;
	sphereFix.restitution = 1.0f;
	sphereFix.density = 20.0f;
	_sphere->CreateFixture(&sphereFix);
	 

	boxBB = box->boundingBox();
		 boxDef.userData = box;
		 boxDef.type = b2_dynamicBody;
		 boxDef.linearVelocity.Set(0.0f,0.0f);
		 boxDef.angularVelocity = 0.0f;
		 boxDef.linearDamping = 0.0f;
		 boxDef.angularDamping = 0.0f;
		 boxDef.allowSleep = bool(4);
		 boxDef.awake = bool(2);
		 boxDef.fixedRotation = bool(0);
		 boxDef.bullet = bool(0);
		 boxDef.active = bool(32);
		 boxDef.gravityScale = 1.0f;
		 boxDef.position.Set(350.0f / PTM_RATIO,300.0f / PTM_RATIO);
		 _box       = m_world->CreateBody(&boxDef);
		 b2PolygonShape boxShape;

		 boxShape.SetAsBox(30  / PTM_RATIO, 30 / PTM_RATIO);
		// boxShape.SetAsBox(boxBB.size.width /PTM_RATIO,boxBB.size.height /PTM_RATIO,b2Vec2(0.0f,0.0f),0.0f);
		 b2FixtureDef boxFix;
		 boxFix.shape = &boxShape;
		 boxFix.density = 1.0f;
		 boxFix.friction = 2.0f;
		 boxFix.isSensor = bool(0);
		 boxFix.filter.categoryBits = uint16(1);
		 boxFix.filter.maskBits = uint16(65535);
		 boxFix.filter.groupIndex = int16(0);

		 boxFix.restitution = 0.0f;
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




b2Body** bodies = (b2Body**)b2Alloc(18 * sizeof(b2Body*));
b2Joint** joints = (b2Joint**)b2Alloc(0 * sizeof(b2Joint*));


{
  b2BodyDef bd;
  bd.type = b2BodyType(0);
  bd.position.Set(390.0f / PTM_RATIO,3.0f / PTM_RATIO);
  bd.angle = 0.0f;
  bd.linearVelocity.Set(0.0f, 0.0f);
  bd.angularVelocity = 0.0;
  bd.linearDamping = 0.0f;
  bd.angularDamping = 0.0f;
  bd.allowSleep = bool(4);
  bd.awake = bool(2);
  bd.fixedRotation = bool(0);
  bd.bullet = bool(0);
  bd.active = bool(32);
  bd.gravityScale = 1.0f;
  bodies[0] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
  
    fd.restitution = 0.0f;
    
    fd.isSensor = bool(1);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    

	shape.SetAsBox(screenSize.width / PTM_RATIO,400.0f / PTM_RATIO,b2Vec2(0.0f,0.0f),0.0f);

    fd.shape = &shape;

    bodies[0]->CreateFixture(&fd);
  }
} 


//boat?
{
  b2BodyDef bd;
  bd.type = b2BodyType(2);
  bd.position.Set(420.0f /  PTM_RATIO, 410.0f  /  PTM_RATIO);
  bd.angle = 3.824857473373413e-01f;
  bd.linearVelocity.Set(0.000000000000000e+00f, 0.000000000000000e+00f);
  bd.angularVelocity = 0.000000000000000e+00f;
  bd.linearDamping = 0.000000000000000e+00f;
  bd.angularDamping = 0.000000000000000e+00f;
  bd.allowSleep = bool(4);
  bd.awake = bool(2);
  bd.fixedRotation = bool(0);
  bd.bullet = bool(0);
  bd.active = bool(32);
  bd.gravityScale = 1.000000000000000e+00f;
  bodies[1] = m_world->CreateBody(&bd);

  {
    b2FixtureDef fd;
    fd.friction = 2.000000029802322e-01f;
    fd.restitution = 0.000000000000000e+00f;
    fd.density = 1.000000000000000e+00f;
    fd.isSensor = bool(0);
    fd.filter.categoryBits = uint16(1);
    fd.filter.maskBits = uint16(65535);
    fd.filter.groupIndex = int16(0);
    b2PolygonShape shape;
    b2Vec2 vs[8];
    vs[0].Set(2.595919609069824e+00f, -1.319291234016418e+00f);
    vs[1].Set(-2.777174711227417e+00f, 9.063234329223633e-01f);
    vs[2].Set(-1.861940383911133e+00f, -4.768543243408203e-01f);
    vs[3].Set(-1.460509777069092e+00f, -1.000003814697266e+00f);
    vs[4].Set(-9.373636245727539e-01f, -1.401435852050781e+00f);
    vs[5].Set(-3.281402587890625e-01f, -1.653779983520508e+00f);
    vs[6].Set(3.256297111511230e-01f, -1.739847183227539e+00f);
    vs[7].Set(9.794044494628906e-01f, -1.653779983520508e+00f);
    shape.Set(vs, 8);

    fd.shape = &shape;

    bodies[1]->CreateFixture(&fd);
  }
}

        




b2Free(joints);
b2Free(bodies);
joints = NULL;
bodies = NULL;






}




void HelloWorld::draw(void)
{

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    m_world->DrawDebugData();

    kmGLPopMatrix();

    
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

