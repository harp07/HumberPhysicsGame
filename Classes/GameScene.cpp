#include "GameScene.h"

using namespace cocos2d;

CCScene* GameScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    bool bRet = false;
    do 
	{
        CC_BREAK_IF(! CCLayer::init());
		GameWorld::worldInstance()->setLayer(this);
		gravity = b2Vec2(0.0,-9.8);
		GameWorld::worldInstance()->getWorld()->SetGravity(gravity);
		GameWorld::worldInstance()->createWorld();
		schedule(schedule_selector(GameScene::update),1/60);
		Camera::cameraInstance()->setLayer(this);
		this->setTouchEnabled(true);
        bRet = true;
    } while (0);

    return bRet;
}

void GameScene::update(float dt)
{
	int32 velocityIterations = 10;
	int32 positionIterations = 10;
	GameWorld::worldInstance()->updateWorld(dt);
}

void GameScene::ccTouchesBegan(CCSet *touches, CCEvent* event){
	CCPoint targetPosition = ccp(GameWorld::worldInstance()->getPlayer()->GetPosition().x,GameWorld::worldInstance()->getPlayer()->GetPosition().y);
	Camera::cameraInstance()->setFocus(ccp(targetPosition.x/PTM_RATIO,targetPosition.y/PTM_RATIO));
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	Camera::cameraInstance()->setLocation(ccp(location.x/PTM_RATIO,0.0f));
}

void GameScene::ccTouchesMoved(CCSet *touches, CCEvent* event){
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	Camera::cameraInstance()->moveCamera(ccp(location.x/PTM_RATIO,0.0f));
}

void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event){
	Camera::cameraInstance()->reset();
}

void GameScene::draw(void)
{
	GameWorld::worldInstance()->draw();
}