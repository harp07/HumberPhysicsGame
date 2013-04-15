#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

#define PTM_RATIO 32.0

using namespace cocos2d;
class Globals {
private:
	Globals();
	static Globals* m_Globals;
	CCLayer *mainLayer;
	b2World* m_world;
	float waterHeight;
	float playerHealth;
	float enemyHealth;
	bool unitTurn;
public:
	enum bodyType {BODY_NULL = 0x0000, BODY_GROUND = 0x0001, BODY_WATER = 0x0002, BODY_SHIP = 0x0003, BODY_PROJECTILE = 0x0004, BODY_MISC = 0x0005};
	static Globals* globalsInstance();
	CCSize screenSize();
	void Output(float szFormat);
	void setLayer(CCLayer* layer);
	CCLayer* getLayer();
	void setWorld(b2World* world);
	b2World* getWorld();
	void setWaterheight(float height);
	float getWaterheight();
	void setPlayerHealth(float health);
	float getPlayerHealth();
	void setEnemyHealth(float health);
	float getEnemyHealth();
	void setUnitTurn(bool turn);
	bool getUnitTurn();
};

#endif