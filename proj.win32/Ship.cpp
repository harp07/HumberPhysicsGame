#include "Ship.h"

#define weaponScale 0.01f

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
			initWeapon(layer,uType,sType);
		} else if (uType == ENEMY){
			obj = new GameObject("ShipFlipped",Globals::globalsInstance()->screenSize().width/1.5,waterHeight+10,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			enemyBody = obj->objBody;
			enemySprite = obj->objSprite;
			setEnemyType(sType);
			initWeapon(layer,uType,sType);
		}
		factorX = 4.0;
		factorY = 6.0;
	} else if (sType == SUBMARINE){
		if(uType == PLAYER){
			obj = new GameObject("Submarine",Globals::globalsInstance()->screenSize().width/4,waterHeight-30,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			playerBody = obj->objBody;
			playerSprite = obj->objSprite;
			setPlayerType(sType);
			initWeapon(layer,uType,sType);
		} else if (uType == ENEMY){
			obj = new GameObject("SubmarineFlipped",Globals::globalsInstance()->screenSize().width/1.5,waterHeight-30,1.0f);
			obj->spriteInit(layer,GameObject::MIDDLEGROUND);
			obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Ships.plist");
			enemyBody = obj->objBody;
			enemySprite = obj->objSprite;
			setEnemyType(sType);
			initWeapon(layer,uType,sType);
		}
		factorX = 1.8;
		factorY = 4.0;
	}
}

void Ship::initWeapon(CCLayer* layer, userType uType, shipType sType){
	if(uType == PLAYER){
		if(sType == SUBMARINE){
			playerWeapon = new GameObject("ball",playerSprite->getPosition().x+playerSprite->getContentSize().width/2,playerSprite->getPosition().y,weaponScale);
			playerWeapon->spriteInit(layer,GameObject::MIDDLEGROUND);
			playerWeapon->physicsInit(Globals::globalsInstance()->getWorld(),GameObject::SHAPE_BOX,GameObject::BODY_DYNAMIC);
			playerWeapon->objBody->SetActive(false);
		} else if (sType == SHIP){
			playerWeapon = new GameObject("ball",playerSprite->getPosition().x,playerSprite->getPosition().y,weaponScale);
			playerWeapon->spriteInit(layer,GameObject::MIDDLEGROUND);
			playerWeapon->physicsInit(Globals::globalsInstance()->getWorld(),GameObject::SHAPE_BOX,GameObject::BODY_DYNAMIC);
			playerWeapon->objBody->SetActive(false);
		}
	} else if (uType == ENEMY){
		if(sType == SUBMARINE){
			enemyWeapon = new GameObject("ball",enemySprite->getPosition().x-enemySprite->getContentSize().width/2,enemySprite->getPosition().y,weaponScale);
			enemyWeapon->spriteInit(layer,GameObject::MIDDLEGROUND);
			enemyWeapon->physicsInit(Globals::globalsInstance()->getWorld(),GameObject::SHAPE_BOX,GameObject::BODY_DYNAMIC);
			enemyWeapon->objBody->SetActive(false);
		} else if(sType == SHIP){
			enemyWeapon = new GameObject("ball",enemySprite->getPosition().x,enemySprite->getPosition().y,weaponScale);
			enemyWeapon->spriteInit(layer,GameObject::MIDDLEGROUND);
			enemyWeapon->physicsInit(Globals::globalsInstance()->getWorld(),GameObject::SHAPE_BOX,GameObject::BODY_DYNAMIC);
			enemyWeapon->objBody->SetActive(false);
		}
	}
	//obj->objBody->CreateFixture(&obj->objShapeDef);
	//obj->objBody->CreateFixture(&weapon->objShapeDef);
	//weapon->objBody->SetGravityScale(0.1f);
}

float Ship::getFactorX(){
	return factorX;
}

float Ship::getFactorY(){
	return factorY;
}

CCSprite* Ship::getWeaponSprite(userType uType){
	if(uType == PLAYER){
		return playerWeapon->objSprite;
	} else if (uType == ENEMY){
		return enemyWeapon->objSprite;
	}
}

b2Body* Ship::getWeaponBody(userType uType){
	if(uType == PLAYER){
		return playerWeapon->objBody;
	} else if (uType == ENEMY){
		return enemyWeapon->objBody;
	}
}

void Ship::startContact(b2Vec2 location){
	//Globals::globalsInstance()->Output(location.x*32);
	//Globals::globalsInstance()->Output(location.y*32);
	//explosion(ccp(location.x*32,location.y*32));
	if(!Globals::globalsInstance()->getUnitTurn()){
		Globals::globalsInstance()->setEnemyHealth(Globals::globalsInstance()->getEnemyHealth()-1);
		Globals::globalsInstance()->Output(Globals::globalsInstance()->getEnemyHealth());
	} else if (Globals::globalsInstance()->getUnitTurn()){
		Globals::globalsInstance()->setPlayerHealth(Globals::globalsInstance()->getPlayerHealth()-1);
		Globals::globalsInstance()->Output(Globals::globalsInstance()->getPlayerHealth());
	}
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

void Ship::setPlayerType(shipType sType){
	playerS = sType;
	if(sType == SUBMARINE){
		Globals::globalsInstance()->setPlayerHealth(100.0f);
	} else if (sType == SHIP){
		Globals::globalsInstance()->setPlayerHealth(75.0f);
	}
}
void Ship::setEnemyType(shipType sType){
	enemyS = sType;
	if(sType == SUBMARINE){
		Globals::globalsInstance()->setEnemyHealth(100.0f);
	} else if (sType == SHIP){
		Globals::globalsInstance()->setEnemyHealth(75.0f);
	}
}
Ship::shipType Ship::getPlayerType(){
	return playerS;
}
Ship::shipType Ship::getEnemyType(){
	return enemyS;
}