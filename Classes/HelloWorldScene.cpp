#include "HelloWorldScene.h"

#include "GB2ShapeCache-x.h"
#include <stdio.h>

using namespace cocos2d;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
	{
		
        CC_BREAK_IF(! CCLayer::init());

		 //screenSize = CCDirector::sharedDirector()->getWinSize();
		 GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("boatTest.plist");
		
		 this->setTouchEnabled(true);
		 
		
		
        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);
		

		this->schedule(schedule_selector(HelloWorld::updateGame));
		
		
		pirateShip = CCSprite::create("PirateShipFlip.png");
		CC_BREAK_IF(! pirateShip);

		pirateShip->setScale(0.5);
		pirateShip->setRotation(45);
		addChild(pirateShip);
		
		box = CCSprite::create("wooden_box.jpg");
		 CC_BREAK_IF(! box);

		 ball = CCSprite::create("Rock-01.png");
		 CC_BREAK_IF(! ball);
	    box->setScale(0.09);

		ball->setScale(1.0);

		addChild(box);
		addChild(ball);

		b2Vec2 gravity(1.0f,-9.8f);

		initPhysics(gravity,true);

        bRet = true;
    } while (0);

    return bRet;
}



void HelloWorld::ccTouchesEnded(CCSet* touches,CCEvent* event)
{

	CCSetIterator it;
	CCTouch* touch;

	for(it = touches->begin(); it != touches->end(); it++)
	{
	
		touch = (CCTouch*)(*it);
	
		if(!touch)
			break;

		CCPoint location = touch->getLocation();
		//location = CCDirector::sharedDirector()->convertToGL(location);

		addNewSpriteWithCoords(location);
	}

}
//void HelloWorld::kick()
//{
//	b2Vec2 force = b2Vec2(30,30);
//	_boat->ApplyLinearImpulse(force,_boat->GetPosition());
//
//}
void HelloWorld::updateGame(float dt)
{
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


void HelloWorld::initPhysics(b2Vec2 grav,bool contiousPhysics)
{
	m_world = new b2World(grav);

	m_world->SetContinuousPhysics(contiousPhysics);
	m_world->SetContactListener(&myListener);

	m_DebugDraw = new b2DebugDraw(PTM_RATIO );
		m_world->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
	m_DebugDraw->SetFlags(flags);

	myListener.setWorld(m_world);
	b2Vec2 _waterPos(90.0f,200.0f);
	b2Vec2 _waterSize(Globals::globalsInstance()->screenSize().width / PTM_RATIO,200.0f /PTM_RATIO);
	myListener.CreateWater(_waterPos,_waterSize,2.0f,2.0f);

	/*sphereDef.type = b2_dynamicBody;
	sphereDef.userData = ball;
	sphereDef.position.Set(120.0f/PTM_RATIO,500.0f/PTM_RATIO);
	sphereDef.linearVelocity.Set(0.0f,0.0f);
	sphereDef.linearDamping = 0.0f;

	 
		 sphereDef.angularVelocity = 0.0f;
		 sphereDef.linearDamping = 0.0f;
		 sphereDef.angularDamping = 0.0f;
		 sphereDef.allowSleep = bool(4);
		 sphereDef.awake = bool(2);
		 sphereDef.fixedRotation = bool(0);
		 sphereDef.bullet = bool(0);
		 sphereDef.active = bool(32);
		 sphereDef.gravityScale = 1.0f;
	
	_sphere    = m_world->CreateBody(&sphereDef);
	b2CircleShape sphereShape;

	sphereShape.m_radius = 10.0f /PTM_RATIO;
	b2FixtureDef sphereFix;
	sphereFix.shape = &sphereShape;

	sphereFix.restitution = 0.0f;
	sphereFix.density = 2.0f;
	sphereFix.isSensor = false;

	 sphereFix.filter.categoryBits = uint16(1);
		 sphereFix.filter.maskBits = uint16(65535);
		 sphereFix.filter.groupIndex = int16(0);

	_sphere->CreateFixture(&sphereFix);*/
	 

	
		// boxDef.userData = box;
		// boxDef.type = b2_dynamicBody;
		// boxDef.linearVelocity.Set(0.0f,0.0f);
		// boxDef.angularVelocity = 0.0f;
		// boxDef.linearDamping = 0.0f;
		// boxDef.angularDamping = 0.0f;
		// boxDef.allowSleep = bool(4);
		// boxDef.awake = bool(2);
		// boxDef.fixedRotation = bool(0);
		// boxDef.bullet = bool(0);
		// boxDef.active = bool(32);
		// boxDef.gravityScale = 1.0f;
		// boxDef.position.Set(350.0f / PTM_RATIO,300.0f / PTM_RATIO);
		// _box       = m_world->CreateBody(&boxDef);
		// b2PolygonShape boxShape;

		// boxShape.SetAsBox(10  / PTM_RATIO, 10 / PTM_RATIO);
		//// boxShape.SetAsBox(boxBB.size.width /PTM_RATIO,boxBB.size.height /PTM_RATIO,b2Vec2(0.0f,0.0f),0.0f);
		// b2FixtureDef boxFix;
		// boxFix.shape = &boxShape;
		// boxFix.density = 1.0f;
		// boxFix.friction = 2.0f;
		// boxFix.isSensor = false;
		// boxFix.filter.categoryBits = uint16(1);
		// boxFix.filter.maskBits = uint16(65535);
		// boxFix.filter.groupIndex = int16(0);

		// boxFix.restitution = 0.0f;
		// _box->CreateFixture(&boxFix);

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
		screenBorderShape.Set(lowerRightCorner, upperRightCorner); 
		groundBody->CreateFixture(&screenBorderShape, 0); 
		screenBorderShape.Set(upperRightCorner, upperLeftCorner); 
		groundBody->CreateFixture(&screenBorderShape, 0); 
		screenBorderShape.Set(upperLeftCorner, lowerLeftCorner); 
		groundBody->CreateFixture(&screenBorderShape, 0); 

		



 
  
 


//boat: This creates a boat shape, got from the RUBE.

  //b2BodyDef boatDef;
		//  boatDef.userData = pirateShip;
  //boatDef.type = b2_dynamicBody;

  //boatDef.position.Set(420.0f /  PTM_RATIO, 410.0f  /  PTM_RATIO);
  //boatDef.angle = 3.824857473373413e-01f;
  //boatDef.linearVelocity.Set(0.0f, 0.0f);
  //boatDef.angularVelocity = 0.0f;
  //boatDef.linearDamping = 0.0f;
  //boatDef.angularDamping = 0.0f;
  //boatDef.allowSleep = false;
  //boatDef.awake = true;
  //boatDef.fixedRotation = false;
  //boatDef.bullet = false;
  //boatDef.active = true;
  //boatDef.gravityScale = 1.0f;
  // _boat = m_world->CreateBody(&boatDef);

  //
  //  b2FixtureDef boatFix;
  //  boatFix.friction = 2.0f;
  //  boatFix.restitution = 0.0f;
  //  boatFix.density = 1.0f;
  //  boatFix.isSensor = false;
  //  boatFix.filter.categoryBits = uint16(1);
  //  boatFix.filter.maskBits = uint16(65535);
  //  boatFix.filter.groupIndex = int16(0);
  //  b2PolygonShape boatShape;
  //  b2Vec2 vs[8];
  //  vs[0].Set(2.595919609069824e+00f , -1.319291234016418e+00f);
  //  vs[1].Set(-2.777174711227417e+00f, 9.063234329223633e-01f);
  //  vs[2].Set(-1.861940383911133e+00f, -4.768543243408203e-01f);
  //  vs[3].Set(-1.460509777069092e+00f, -1.000003814697266e+00f);
  //  vs[4].Set(-9.373636245727539e-01f, -1.401435852050781e+00f);
  //  vs[5].Set(-3.281402587890625e-01f, -1.653779983520508e+00f);
  //  vs[6].Set(3.256297111511230e-01f, -1.739847183227539e+00f);
  //  vs[7].Set(9.794044494628906e-01f, -1.653779983520508e+00f);
  //  boatShape.Set(vs, 8);

  //  boatFix.shape = &boatShape;

  //  _boat->CreateFixture(&boatFix);






}

void HelloWorld::addNewSpriteWithCoords(CCPoint p)
{
	string _name = "PirateShip";

	CCSprite *sprite = CCSprite::create((_name+".png").c_str());

	sprite->setPosition(p);
	//sprite->setScale(0.8);

	addChild(sprite);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	
	bodyDef.position.Set(p.x/PTM_RATIO,p.y/PTM_RATIO);
	bodyDef.userData = sprite;
	b2Body *body = m_world->CreateBody(&bodyDef);

	GB2ShapeCache  *_shapeCache = GB2ShapeCache::sharedGB2ShapeCache();
	_shapeCache->addFixturesToBody(body,_name.c_str());
	sprite->setAnchorPoint(_shapeCache->anchorPointForShape(_name.c_str()));

}

void HelloWorld::draw(void)
{
	 

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

	
    m_world->DrawDebugData();

    kmGLPopMatrix();

    CHECK_GL_ERROR_DEBUG();
}

    

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

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


HelloWorld::~HelloWorld()
{
	delete m_world;
	m_world = NULL;

}