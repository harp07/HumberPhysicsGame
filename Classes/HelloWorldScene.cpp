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

		m_DebugDraw = new b2DebugDraw(PTM_RATIO);
		GameWorld::worldInstance()->getWorld()->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		m_DebugDraw->SetFlags(flags);

		GameWorld::worldInstance()->setLayer(this,screenSize);
		//Setting the background also draws over the debug draw
		GameWorld::worldInstance()->setBackground("HelloWorld.png", "CloseNormal.png");
		GameWorld::worldInstance()->getWorld()->SetGravity(gravity);
		GameWorld::worldInstance()->createWorld();
		scheduleUpdate();
		
        bRet = true;
    } while (0);

    return bRet;
}


void HelloWorld::update(float dt)
{
	int32 velocityIterations = 10;
	int32 positionIterations = 10;
	GameWorld::worldInstance()->getWorld()->Step(dt,velocityIterations,positionIterations);
	for (b2Body *body = GameWorld::worldInstance()->getWorld()->GetBodyList(); body != NULL; body = body->GetNext())   
	{  
		if (body->GetUserData()) 
		{  
		CCSprite *sprite = (CCSprite *) body->GetUserData();  
		sprite->setPosition(ccp(body->GetPosition().x*PTM_RATIO, body->GetPosition().y * PTM_RATIO));  
		sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
		}  
	}  
	GameWorld::worldInstance()->getWorld()->ClearForces();
}

void HelloWorld::draw(void){
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    GameWorld::worldInstance()->getWorld()->DrawDebugData();
    kmGLPopMatrix();
}