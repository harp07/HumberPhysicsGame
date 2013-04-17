#ifndef __PROPULSION_H__
#define __PROPULSION_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"

using namespace cocos2d;

class propulsion{

public:

	propulsion(b2Vec2 Center);
	~propulsion();
	void addForce(b2Body *boat,b2Vec2 force);
	b2Vec2 center;


};

#endif