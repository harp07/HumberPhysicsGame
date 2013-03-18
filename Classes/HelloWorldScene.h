#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"
#include "particle.h"

#include "SimpleAudioEngine.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
	b2World *m_world;
	b2DebugDraw *m_DebugDraw;
	b2Vec2 gravity;
	b2BodyDef sphereDef;
	b2Body *_sphere[10];

	b2Body *_box;
	b2BodyDef boxDef;
	particle* p;

		int i;
		int j;
		bool f;
		float x;
		float y;
		
		b2Vec2 vector;
		float desiredAngle;
		float nextAngle;
		float totalRotation;
		float desiredAngularVelocity;
		//CCParticleSystemQuad* m_emitter;
		//this is the variable m_emitter defined in the header
		cocos2d::CCParticleSystem *m_emitter;
		void smoke(CCPoint location);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	void update(float dt);

	virtual void draw(void);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	//void addNewSpriteAtPosition(CCPoint p);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void Keyboard(unsigned char key);
	cocos2d::CCSprite* ball;
	cocos2d::CCSprite* box;


    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__