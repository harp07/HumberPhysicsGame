#ifndef __GLASSBOX_H__
#define __GLASSBOX_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

#define PTM_RATIO 32.0

using namespace cocos2d;

class GlassBox {
private:

	GlassBox();
	static GlassBox* singleGlassBox;
	int currentState;
	float maxDistanceFromPlayer;
	float speed;
	b2Vec2 setNewDestination(b2Vec2 currentPlayerPosition, b2Vec2 currentAIPosition);
	b2Body *tempPlayer;
	b2Body *tempEnemy;
	int nextStep;

public:

	enum State{
		IDLE,
		ATTACKING,
		DEFENDING
	};

	State getAIState();

	void setAIOnBody(b2Body *playerBody, b2Body *aiBody);

	static GlassBox* getGlassBox();

	void update(float dt);
};

#endif //__GLASSBOX__