#include "Ship.h"

using namespace cocos2d;

Ship::Ship(shipType sType, userType uType,float waterHeight, CCLayer* layer, b2World* m_world){
	if(sType == SHIP){
		if(uType == PLAYER){
			obj = new GameObject("Ship",Globals::globalsInstance()->screenSize().width/4,waterHeight+10,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			playerBody = obj->objBody;
			playerSprite = obj->objSprite;
			setPlayerType(sType);
		} else if (uType == ENEMY){
			obj = new GameObject("ShipFlipped",Globals::globalsInstance()->screenSize().width/1.5,waterHeight+10,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			enemyBody = obj->objBody;
			enemySprite = obj->objSprite;
			setEnemyType(sType);
		}
	} else if (sType == SUBMARINE){
		if(uType == PLAYER){
			obj = new GameObject("Submarine",Globals::globalsInstance()->screenSize().width/4,waterHeight-30,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			playerBody = obj->objBody;
			playerSprite = obj->objSprite;
			setPlayerType(sType);
		} else if (uType == ENEMY){
			obj = new GameObject("SubmarineFlipped",Globals::globalsInstance()->screenSize().width/1.5,waterHeight-30,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			enemyBody = obj->objBody;
			enemySprite = obj->objSprite;
			setEnemyType(sType);
		}
	}
}

void Ship::initShip(){
	//shipHealth = 100.0f;
}
/*
void Ship::startContact(b2Vec2 location){
	//Globals::globalsInstance()->Output(location.x*32);
	//Globals::globalsInstance()->Output(location.y*32);
	explosion(ccp(location.x*32,location.y*32));
	//enemyHealth -= 1;
	//Globals::globalsInstance()->Output(enemyHealth);
	//Globals::globalsInstance()->Output(1);
}

void Ship::endContact(){
	//Globals::globalsInstance()->Output(2);
}

void Ship::explosion(CCPoint location){

	m_emitter = CCParticleExplosion::create();
	m_emitter->retain();
	m_emitter->setPosition(location);
	m_emitter->setSpeed(1.0f);
	m_emitter->setLife(0.5f);
	m_emitter->setGravity(ccp(0.0f,-200.0f/PTM_RATIO));
	m_emitter->setTotalParticles(5);

	ccColor4F startColor = {0.0f, 0.0f, 0.0f, 1.0f};
	m_emitter->setStartColor(startColor);

	//ccColor4F startColorVar = {1.0f, 0.1f, 0.1f, 1.0f};
	//m_emitter->setStartColorVar(startColorVar);

	//ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	//m_emitter->setEndColor(endColor);

	//ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
	//m_emitter->setEndColorVar(endColorVar);

	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("ball.png"));
	Globals::globalsInstance()->getLayer()->addChild(m_emitter, GameObject::MIDDLEGROUND);
	m_emitter->setAutoRemoveOnFinish(true);
}
*/
void Ship::setPlayerType(shipType sType){
	playerS = sType;
}
void Ship::setEnemyType(shipType sType){
	enemyS = sType;
}
Ship::shipType Ship::getPlayerType(){
	return playerS;
}
Ship::shipType Ship::getEnemyType(){
	return enemyS;
}