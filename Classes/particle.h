#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"

using namespace cocos2d;

class particle 
{
public:

	particle(CCLayer *l);
	~particle();
	void update(float dt);
	void smoke(CCPoint location);
	void fire(CCPoint location);
	void rain(float rainStartX,float rainEndX,float rainHight);
	void setImage(std::string image);


	/*float particleLife;
	float fountainLife;
	int thickness;
	bool crate;
	CCPoint location;
	float count;
	int time;*/


	float smokeParticleLife;
	float smokeFountainLife;
	int smokeThickness;
	bool smokeCrate;
	CCPoint smokeLocation;
	float smokeCount;
	int smokeTime;

	float fireParticleLife;
	float fireFountainLife;
	int fireThickness;
	bool fireCrate;
	CCPoint fireLocation;
	float fireCount;
	int fireTime;

	float rainParticleLife;
	float rainFountainLife;
	int rainThickness;
	bool rainCrate;
	CCPoint rainLocation;
	float rainCount;
	int rainTime;
	float rainStartX;
	float rainEndX;
	float rainHight;


	float wind;
	CCLayer* Layer;
	bool image;
	cocos2d::CCParticleSystem *m_emitter;
	string imageImage;

};

#endif