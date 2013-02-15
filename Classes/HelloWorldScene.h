#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"

#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
	b2World *m_world;
	b2DebugDraw *m_DebugDraw;
	b2Vec2 gravity;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	void update(float dt);

	cocos2d::CCSprite* ball;
	cocos2d::CCSprite* box;

	
	virtual void draw(void);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	void kick();

	void initPhysics();
	   	
	b2Body *_sphere;		
	b2BodyDef sphereDef;

	b2Body *_box;
	b2BodyDef boxDef;
	cocos2d::CCSize screenSize;

	cocos2d::CCRect boxBB;

	

	//box2D functions
	


    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__