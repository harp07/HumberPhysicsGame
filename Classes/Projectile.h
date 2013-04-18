#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "GameObject.h"
#include "Globals.h"
#include "SimpleAudioEngine.h"

class Projectile{
public:
	GameObject *obj;
	enum projectileType {PROJ_NULL = 0, PROJ_TORPEDO, PROJ_CANNONBALL};

	Projectile(float px, float py, projectileType projType,b2Vec2 position, CCLayer *layer, b2World *m_world, float sign, float angle);
	~Projectile();

	void startContact(b2Body* proj,b2Vec2 location);
	void endContact();

	void explosion(CCPoint location);
	cocos2d::CCParticleSystem *m_emitter;
	void initBubbles(CCPoint location);
	std::list<b2Body*> projectilesScheduledForRemoval;

	void SetPowerX(float px);
	void SetPowerY(float py);

	float GetPowerX();
	float GetPowerY();
private:
	CCSprite* sprite;
	b2Body* body;
	float powerx, powery;
};

#endif