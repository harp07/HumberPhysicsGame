#ifndef __SHIP_H__
#define __SHIP_H__

#include "GameObject.h"
#include "Globals.h"

using namespace cocos2d;

class Ship {
public:
	b2Body *playerBody;
	CCSprite *playerSprite;
	b2Body *enemyBody;
	CCSprite *enemySprite;
	GameObject *obj;
	float playerHealth, enemyHealth;
	bool m_contacting;
	enum shipType { SHIP_NULL = 0, SHIP, SUBMARINE};
	enum userType { USER_NULL = 0, PLAYER, ENEMY};
	
	Ship(shipType sType, userType uType, float waterHeight, CCLayer* layer, b2World* m_world);
	void startContact(b2Vec2 location);
	void endContact();
	void initWeapon(CCLayer* layer, userType uType, shipType sType);
	CCSprite* getWeaponSprite(userType uType);
	b2Body* getWeaponBody(userType uType);
	void explosion(CCPoint location);
	void setPlayerType(shipType sType);
	void setEnemyType(shipType sType);
	shipType getPlayerType();
	shipType getEnemyType();
	cocos2d::CCParticleSystem *m_emitter;
	float getFactorX();
	float getFactorY();
	
private:
	shipType playerS;
	shipType enemyS;
	GameObject *playerWeapon;
	GameObject *enemyWeapon;
	float factorX, factorY;
};

#endif