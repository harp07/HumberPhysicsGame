#include "Ship.h"

using namespace cocos2d;

Ship::Ship(shipType sType, userType uType,float waterHeight, CCLayer* layer, b2World* m_world){
	GameObject *obj;
	if(sType == SHIP){
		if(uType == PLAYER){
			obj = new GameObject("Ship",Globals::globalsInstance()->screenSize().width/4,waterHeight+10,1.0f);
		} else if (uType == ENEMY){
			obj = new GameObject("ShipFlipped",Globals::globalsInstance()->screenSize().width/1.1,waterHeight+10,1.0f);
		}
		obj->spriteInit(layer,GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
		body = obj->objBody;
		sprite = obj->objSprite;
	} else if (sType == SUBMARINE){
		if(uType == PLAYER){
			obj = new GameObject("Submarine",Globals::globalsInstance()->screenSize().width/4,waterHeight-30,1.0f);
		} else if (uType == ENEMY){
			obj = new GameObject("SubmarineFlipped",Globals::globalsInstance()->screenSize().width/1.1,waterHeight-30,1.0f);
		}
		obj->spriteInit(layer,GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
		body = obj->objBody;
		sprite = obj->objSprite;
	}
	initShip();
}

void Ship::initShip(){
	shipHealth = 100.0f;
}