#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"
#include "BouyancyContactListener.h"
#include "Globals.h"
#include "GameObject.h"

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
	bool debugDrawBool;
	bool projectileFired;
	float shots;
public:
	static GameWorld* worldInstance();
	void setLayer(CCLayer* layer);
	b2World* getWorld();
	void createWorld();
	void draw();
	void setBackground(const char* _location);
	void updateWorld(float dt);
	void shoot();
	void debugVisuals();
	b2Body* getPlayer();
	void addObjects();
	BouyancyContactListener myListener;
	CCSprite* playerSprite;
	b2Body* playerBody;
	CCSprite* defaultSprite;
	GameObject *player;
	GameObject *enemy;
	GameObject *submarine;
	b2Vec2 _waterPos;
	b2Vec2 _waterSize;
	GameObject* projectile;
};

#endif  // __GAME_WORLD__