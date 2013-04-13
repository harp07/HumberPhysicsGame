#ifndef __SHIP_H__
#define __SHIP_H__

#include "GameObject.h"
#include "Globals.h"

using namespace cocos2d;

class Ship{
public:
	b2Body *body;
	CCSprite *sprite;
	float shipHealth;
	enum shipType { SHIP_NULL = 0, SHIP, SUBMARINE};
	enum userType { USER_NULL = 0, PLAYER, ENEMY};
	
	Ship(shipType sType, userType uType, float waterHeight, CCLayer* layer, b2World* m_world);
private:
	void initShip();
};

#endif