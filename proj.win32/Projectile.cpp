#include "Projectile.h"

using namespace cocos2d;

Projectile::Projectile(projectileType projType,b2Vec2 position, CCLayer *layer, b2World *m_world){
	if(projType == PROJ_CANNONBALL){
		obj = new GameObject("CannonBall",position.x+50,position.y+20,1.0f);
		obj->spriteInit(layer, GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Projectiles.plist");
		obj->objBody->ApplyForceToCenter(b2Vec2((1000.0f)/PTM_RATIO,(2000.0f)/PTM_RATIO));
	} else if (projType == PROJ_TORPEDO){
		obj = new GameObject("Torpedo",position.x+70,position.y,1.0f);
		obj->spriteInit(layer, GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Projectiles.plist");
		obj->objBody->ApplyForceToCenter(b2Vec2((250000.0f + rand() % 1)/PTM_RATIO,(2000.0f)/PTM_RATIO));
	}
}

void Projectile::startContact(b2Vec2 location){
	//Globals::globalsInstance()->Output(location.x*32);
	//Globals::globalsInstance()->Output(location.y*32);
	explosion(ccp(location.x*32,location.y*32));
	//enemyHealth -= 1;
	//Globals::globalsInstance()->Output(enemyHealth);
	//Globals::globalsInstance()->Output(1);
}

void Projectile::endContact(){
	//Globals::globalsInstance()->Output(2);
}

void Projectile::explosion(CCPoint location){

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