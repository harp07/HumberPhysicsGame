#ifndef __BOUYANCY_CONTACT_LISTENER_H__
#define __BOUYANCY_CONTACT_LISTENER_H__

#include "Box2D\Box2D.h"

#include "Globals.h"
#include <set>
#include <vector>
#include <math.h>

class BouyancyContactListener : public b2ContactListener
{
private:
	b2World* m_world;
	b2Body* _water;
	b2BodyDef waterDef;
public:
	typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;
	std::set<fixturePair> m_fixturePairs;

	BouyancyContactListener();
	~BouyancyContactListener();

	 void BeginContact(b2Contact* contact);

	 void EndContact(b2Contact* contact);
	



	

	float rnd_1();
	b2Vec2 ComputeCentroid(std::vector<b2Vec2> vs, float& area);
	

	bool inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p); 



	b2Vec2 intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e);


	bool findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, std::vector<b2Vec2>& outputVertices);

	void update(float dt);
	void CreateWater(b2Vec2 pos,b2Vec2 size, float density,float friction);
	void setWorld(b2World* world);
	b2World* getWorld();

};

#endif