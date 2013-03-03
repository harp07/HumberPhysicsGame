#ifndef __GAME_WORLD__
#define __GAME_WORLD__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

using namespace cocos2d;
class GameWorld
{
private:
	GameWorld();
	static GameWorld* m_singleton;
	b2World* m_world;
	b2DebugDraw *m_DebugDraw;
	CCLayer* mainLayer;
	CCSize screenSize;
public:
	static GameWorld* worldInstance();
	void setLayer(CCLayer* layer, CCSize winSize);
	b2World* getWorld();
	void createWorld();
	void draw();
	//Sets the background for the scene
	void setBackground(const char* _img1, const char* _img2);
	//Set the parallax background
	void setParallax();
};

#endif  // __GAME_WORLD__