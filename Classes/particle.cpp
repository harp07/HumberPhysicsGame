#include "particle.h"
#include "stdlib.h"

#define PTM_RATIO 32.0

using namespace cocos2d;

particle::particle(CCLayer *l){

	image = false;
	Layer = l;
	wind = 0.0f;

	smokeCrate = false;
	smokeCount = 50.0f;
	smokeTime = 0;
	smokeFountainLife = 50.0f;
	smokeParticleLife = 2.0f;
	smokeThickness = 10;

	fireCrate = false;
	fireCount = 50.0f;
	fireTime = 0;
	fireFountainLife = 50.0f;
	fireParticleLife = 1.0f;
	fireThickness = 5;

	rainCrate = false;
	rainCount = 1.0f;
	rainTime = 0;
	rainFountainLife = 200.0f;
	rainParticleLife = 20.0f;
	rainThickness = 10;

	rainStartX = 0.0f;
	rainEndX = 0.0f;
	rainHight = 0.0f;

}

particle::~particle(){
}

void particle::update(float dt)
{
	if(smokeCrate){
		m_emitter = CCParticleSmoke::create();
		m_emitter->retain();
		m_emitter->setPosition(smokeLocation);

		ccColor4F startColor = {0.1f, 0.1f, 0.1f, 1.0f};
		m_emitter->setStartColor(startColor);

		//ccColor4F startColorVar = {0.5f, 0.f, 0.5f, 1.0f};
		//m_emitter->setStartColorVar(startColorVar);

		ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
		m_emitter->setEndColor(endColor);

		ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
		m_emitter->setEndColorVar(endColorVar);

		m_emitter->setScale(0.5f);
		m_emitter->setGravity(ccp(wind,100.0f));
		m_emitter->setLife(smokeParticleLife);
		m_emitter->setTotalParticles(10);
		m_emitter->setDuration(1.0f);

		Layer->addChild(m_emitter, 1);
		if(image){
		m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(imageImage.c_str()));//imageImage go's here, fix later
		}

		m_emitter->setAutoRemoveOnFinish(true);
		smokeCrate = false;
		smokeTime = 0;
		smokeCount += 1.0f;
	}else{
		if(smokeTime > smokeThickness){
			if(smokeCount < smokeFountainLife){
				smokeCrate = true;
			}
		}
	}

	if(fireCrate){
		m_emitter = CCParticleFire::create();
		m_emitter->retain();
		m_emitter->setPosition(fireLocation);

		ccColor4F startColor = {0.1f, 0.1f, 0.1f, 1.0f};
		m_emitter->setStartColor(startColor);

		ccColor4F startColorVar = {0.5f, 0.f, 0.5f, 1.0f};
		m_emitter->setStartColorVar(startColorVar);

		ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
		m_emitter->setEndColor(endColor);

		ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
		m_emitter->setEndColorVar(endColorVar);

		m_emitter->setScale(0.5f);
		m_emitter->setGravity(ccp(wind,100.0f));
		m_emitter->setLife(fireParticleLife);
		m_emitter->setTotalParticles(10);
		m_emitter->setDuration(1.0f);

		Layer->addChild(m_emitter, 1);
		if(image){
		m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(imageImage.c_str()));//imageImage go's here, fix later
		}

		m_emitter->setAutoRemoveOnFinish(true);
		fireCrate = false;
		fireTime = 0;
		fireCount += 1.0f;
	}else{
		if(fireTime > fireThickness){
			if(fireCount < fireFountainLife){
				fireCrate = true;
			}
		}
	}

	if(rainCrate){
		m_emitter = CCParticleSmoke::create();
		m_emitter->retain();
		m_emitter->setPosition(rainLocation);

		ccColor4F startColor = {0.1f, 0.1f, 0.1f, 1.0f};
		m_emitter->setStartColor(startColor);

		ccColor4F startColorVar = {0.5f, 0.f, 0.5f, 1.0f};
		m_emitter->setStartColorVar(startColorVar);

		ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
		m_emitter->setEndColor(endColor);

		ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
		m_emitter->setEndColorVar(endColorVar);

		m_emitter->setScale(0.5f);
		m_emitter->setGravity(ccp(wind,-200.0f));
		m_emitter->setLife(rainParticleLife);
		m_emitter->setTotalParticles(10);
		m_emitter->setDuration(1.0f);

		Layer->addChild(m_emitter, 1);
		if(image){
			m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage(imageImage.c_str()));//imageImage go's here, fix later
		}

		m_emitter->setAutoRemoveOnFinish(true);
		rainCrate = false;
		rainTime = 0;
		rainCount += 1.0f;
	}else{
		if(rainTime > rainThickness){
			if(rainCount < rainFountainLife){
				rainCrate = true;
				if(rainLocation.x < rainEndX){
					rainLocation.x += rand()% 10 + 1;
				}else{
					rainLocation.x = rainStartX;
				}
			}
		}
	}

	smokeTime++;
	fireTime++;
	rainTime++;
}
void particle::smoke(CCPoint l){
	smokeLocation = l;
	smokeCrate = true;
	smokeCount = 0.0f;
	smokeFountainLife = 50.0f;
}
void particle::fire(CCPoint l){
	fireLocation = l;
	fireCrate = true;
	fireCount = 0.0f;

	smokeLocation = l;
	smokeCrate = true;
	smokeCount = 0.0f;
	smokeFountainLife = fireFountainLife * 2;
}
void particle::rain(float StartX,float EndX,float Hight){
	rainLocation = ccp(StartX,Hight);
	rainCrate = true;
	rainCount = 0.0f;
	rainFountainLife = 50.0f;

	rainStartX = StartX;
	rainEndX = EndX;
	rainHight = Hight;
}
void particle::setImage(std::string image){
	imageImage = image;
	image = true;
}