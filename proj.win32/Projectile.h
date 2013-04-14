#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "GameObject.h"
#include "Globals.h"

class Projectile{
public:
	GameObject *obj;
	enum projectileType {PROJ_NULL = 0, PROJ_TORPEDO, PROJ_CANNONBALL};

	Projectile(projectileType projType,b2Vec2 position, CCLayer *layer, b2World *m_world);
	~Projectile();

	void startContact(b2Vec2 location);
	void endContact();

	void explosion(CCPoint location);
	cocos2d::CCParticleSystem *m_emitter;
};

#endif