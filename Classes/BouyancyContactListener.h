#include "Box2D\Box2D.h"
#include "BouyancyFunctions.h"
#include "b2DebugDraw.h"
class BouyancyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	std::set<fixturePair> m_fixturePairs;


	void updateObjects();
};