#include "Projectile.h"

using namespace cocos2d;

Projectile::Projectile(float px, float py, projectileType projType,b2Vec2 position, CCLayer *layer, b2World *m_world, float sign,float angle){
	if(projType == PROJ_CANNONBALL){
		SetPowerX(px);
		SetPowerY(py);
		obj = new GameObject("CannonBall",position.x+(10*sign),(position.y),1.0f);
		obj->spriteInit(layer, GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Projectiles.plist");
		//obj->objBody->SetTransform(obj->objBody->GetPosition(),angle*(sign));
		obj->objBody->ApplyForceToCenter(b2Vec2((powerx*(sign))/PTM_RATIO,(powery)/PTM_RATIO));
		sprite = obj->objSprite;
		body = obj->objBody;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Cannon.wav", false);
	} else if (projType == PROJ_TORPEDO && sign == 1){
		SetPowerX(px);
		SetPowerY(py);
		obj = new GameObject("TorpedoFlipped",(position.x+10),position.y,1.0f);
		obj->spriteInit(layer, GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Projectiles.plist");
		obj->objBody->SetTransform(obj->objBody->GetPosition(),angle);
		obj->objBody->ApplyForceToCenter(b2Vec2((powerx*(sign))/PTM_RATIO,(powery)/PTM_RATIO));
		sprite = obj->objSprite;
		body = obj->objBody;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("torpedo_launch.wav", false);
	} else if (projType == PROJ_TORPEDO && sign == -1){
		SetPowerX(px);
		SetPowerY(py);
		obj = new GameObject("Torpedo",(position.x-10),position.y,1.0f);
		obj->spriteInit(layer, GameObject::MIDDLEGROUND);
		obj->physicsInit(m_world,GameObject::SHAPE_PLIST,GameObject::BODY_DYNAMIC,"Projectiles.plist");
		obj->objBody->SetTransform(obj->objBody->GetPosition(),angle);
		obj->objBody->ApplyForceToCenter(b2Vec2((powerx*(sign))/PTM_RATIO,(powery)/PTM_RATIO));
		sprite = obj->objSprite;
		body = obj->objBody;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("torpedo_launch.wav", false);
	}
}

void Projectile::SetPowerX(float px)
{
	powerx = px;
}

void Projectile::SetPowerY(float py)
{
	powery = py;
}

float Projectile::GetPowerX()
{
	return powerx;
}

float Projectile::GetPowerY()
{
	return powery;
}


Projectile::~Projectile(){
	Globals::globalsInstance()->getLayer()->removeChild(sprite,true);
	Globals::globalsInstance()->getWorld()->DestroyBody(body);
}



void Projectile::startContact(b2Body* proj, b2Vec2 location){
	//Globals::globalsInstance()->Output(location.x*32);
	//Globals::globalsInstance()->Output(location.y*32);
	explosion(ccp(location.x*32,location.y*32));
	//projectilesScheduledForRemoval.push_back(proj);
	//enemyHealth -= 1;
	//Globals::globalsInstance()->Output(enemyHealth);
	//Globals::globalsInstance()->Output(1);
}

void Projectile::endContact(){
	//Globals::globalsInstance()->Output(2);
}

void Projectile::explosion(CCPoint location){

	if(location.y > Globals::globalsInstance()->getWaterheight()){
		//Globals::globalsInstance()->Output(Globals::globalsInstance()->getWaterheight());
		m_emitter = CCParticleFire::create();
		m_emitter->retain();
		m_emitter->setPosition(location);
		m_emitter->setScale(0.3);
		//m_emitter->setSpeed(0.1f);
		//m_emitter->setLife(0.1f);
		m_emitter->setDuration(0.1f);
		m_emitter->setGravity(ccp(0.0f,20.0f/PTM_RATIO));
		//m_emitter->setTotalParticles(100);

		//ccColor4F startColor = {1.0f, 1.0f, 0.0f, 1.0f};
		//m_emitter->setStartColor(startColor);

		//ccColor4F startColorVar = {1.0f, 0.1f, 0.1f, 1.0f};
		//m_emitter->setStartColorVar(startColorVar);

		//ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
		//m_emitter->setEndColor(endColor);

		//ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
		//m_emitter->setEndColorVar(endColorVar);

		//m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("ball.png"));
	} else {
		m_emitter = CCParticleSmoke::create();
		m_emitter->retain();
		m_emitter->setPosition(location);
		m_emitter->setScale(0.1);
		m_emitter->setLife(0.5f);
		m_emitter->setLifeVar(0.0f);
		m_emitter->setDuration(0.1f);
		//m_emitter->setSpeed(1.0f);
		//m_emitter->setLife(0.1f);
		m_emitter->setGravity(ccp(0.0f,1000.0f));
		m_emitter->setEmitterMode(kCCParticleModeGravity);
		//m_emitter->setTotalParticles(50);
		//m_emitter->setDuration(1.0f);

		ccColor4F startColor = {0.0f, 0.0f, 0.5f, 1.0f};
		m_emitter->setStartColor(startColor);

		ccColor4F startColorVar = {0.0f, 0.0f, 0.5f, 1.0f};
		m_emitter->setStartColorVar(startColorVar);

		ccColor4F endColor = {0.0f, 0.0f, 1.0f, 0.2f};
		m_emitter->setEndColor(endColor);

		ccColor4F endColorVar = {0.0f, 0.0f, 1.0f, 0.2f};
		m_emitter->setEndColorVar(endColorVar);
	}
	Globals::globalsInstance()->getLayer()->addChild(m_emitter, GameObject::MIDDLEGROUND);
	m_emitter->setAutoRemoveOnFinish(true);
}

void Projectile::initBubbles(CCPoint location){
	m_emitter = CCParticleSmoke::create();
	m_emitter->retain();
	m_emitter->setPosition(location);
	m_emitter->setScale(0.5);
	m_emitter->setLife(0.5f);
	m_emitter->setLifeVar(0.0f);
	m_emitter->setDuration(0.5f);
	m_emitter->setGravity(ccp(0.0f,1000.0f));
	m_emitter->setEmitterMode(kCCParticleModeGravity);

	ccColor4F startColor = {0.0f, 0.0f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);

	ccColor4F startColorVar = {0.0f, 0.0f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);

	ccColor4F endColor = {0.0f, 0.0f, 1.0f, 0.2f};
	m_emitter->setEndColor(endColor);

	ccColor4F endColorVar = {0.0f, 0.0f, 1.0f, 0.2f};
	m_emitter->setEndColorVar(endColorVar);
	Globals::globalsInstance()->getLayer()->addChild(m_emitter, GameObject::MIDDLEGROUND);
	m_emitter->setAutoRemoveOnFinish(true);
}