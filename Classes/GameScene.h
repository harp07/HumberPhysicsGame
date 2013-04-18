#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"
#include "Camera.h"
#include "GameWorld.h"
#include "Globals.h"

using namespace cocos2d;

class GameScene : public cocos2d::CCLayer
{
public:
	b2World *m_world;
	b2DebugDraw *m_DebugDraw;
	b2Vec2 gravity;
	b2Body *_sphere;
	void ground();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	void update(float dt);

	virtual void draw(void);
    // a selector callback
	void ccTouchesBegan(CCSet *touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif  // __HELLOWORLD_SCENE_H__