#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "b2DebugDraw.h"
#include "Box2D/Box2D.h"
#include "BouyancyContactListener.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:

	b2DebugDraw *m_DebugDraw;

	typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;

	
	BouyancyContactListener myListener;
	~HelloWorld();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void addNewSpriteWithCoords(cocos2d::CCPoint p);
	
	void initPhysics(b2Vec2 grav,bool contiousPhysics);

	void CreateWater(b2Vec2 pos,b2Vec2 size, float density,float friction);

	virtual void draw(void);

	virtual void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);

	void updateGame(float dt);
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
	b2World* m_world;

	
	b2Body* _water;
	b2BodyDef waterDef;



	cocos2d::CCSize screenSize;
	//old way of setting body with sprites //
	/* 
	b2Body* _boat;
	b2BodyDef boatDef;
	cocos2d::CCSprite* pirateShip;
	
	b2Body* _box;
	b2BodyDef boxDef;
	cocos2d::CCSprite* box;

	b2Body* _sphere;
	b2BodyDef sphereDef;
	cocos2d::CCSprite* ball;
	
	*/
	
	
	
};


#endif  // __HELLOWORLD_SCENE_H__