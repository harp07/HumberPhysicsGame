#include "BouyancyContactListener.h"


BouyancyContactListener::BouyancyContactListener()
{}

BouyancyContactListener::~BouyancyContactListener()
{}



void BouyancyContactListener::BeginContact(b2Contact* contact)
{

b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        //This assumes every sensor fixture is fluid, and will interact
        //with every dynamic body.
        if ( fixtureA->IsSensor() &&
             fixtureB->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.insert( make_pair(fixtureA, fixtureB) );
        else if ( fixtureB->IsSensor() &&
                  fixtureA->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.insert( make_pair(fixtureB, fixtureA) );
}


void BouyancyContactListener::EndContact(b2Contact* contact)
{

	 b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        //This check should be the same as for BeginContact, but here
        //we remove the fixture pair
        if ( fixtureA->IsSensor() &&
             fixtureB->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.erase( make_pair(fixtureA, fixtureB) );
        else if ( fixtureB->IsSensor() &&
                  fixtureA->GetBody()->GetType() == b2_dynamicBody )
            m_fixturePairs.erase( make_pair(fixtureB, fixtureA) );

}


float BouyancyContactListener::rnd_1()
{
    return rand() / (float)RAND_MAX;
}

b2Vec2 BouyancyContactListener::ComputeCentroid(std::vector<b2Vec2> vs, float& area)
	{
		int count = (int)vs.size();
		b2Assert(count >= 3);

		b2Vec2 c; c.Set(0.0f, 0.0f);
		area = 0.0f;

		// pRef is the reference point for forming triangles.
		// It's location doesn't change the result (except for rounding error).
		b2Vec2 pRef(0.0f, 0.0f);

		const float32 inv3 = 1.0f / 3.0f;

		for (int32 i = 0; i < count; ++i)
		{
			// Triangle vertices.
			b2Vec2 p1 = pRef;
			b2Vec2 p2 = vs[i];
			b2Vec2 p3 = i + 1 < count ? vs[i+1] : vs[0];

			b2Vec2 e1 = p2 - p1;
			b2Vec2 e2 = p3 - p1;

			float32 D = b2Cross(e1, e2);

			float32 triangleArea = 0.5f * D;
			area += triangleArea;

			// Area weighted centroid
			c += triangleArea * inv3 * (p1 + p2 + p3);
		}

		// Centroid
		if (area > b2_epsilon)
			c *= 1.0f / area;
		else
			area = 0;
		return c;
	}

bool BouyancyContactListener::inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p) {
		return (cp2.x-cp1.x)*(p.y-cp1.y) > (cp2.y-cp1.y)*(p.x-cp1.x);
	}

b2Vec2 BouyancyContactListener::intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e) {
		b2Vec2 dc( cp1.x - cp2.x, cp1.y - cp2.y );
		b2Vec2 dp( s.x - e.x, s.y - e.y );
		float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
		float n2 = s.x * e.y - s.y * e.x;
		float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
		return b2Vec2( (n1*dp.x - n2*dc.x) * n3, (n1*dp.y - n2*dc.y) * n3);
	}


bool BouyancyContactListener::findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, std::vector<b2Vec2>& outputVertices)
	{
		//currently this only handles polygon vs polygon
		if ( fA->GetShape()->GetType() != b2Shape::e_polygon ||
			fB->GetShape()->GetType() != b2Shape::e_polygon )
			return false;

		b2PolygonShape* polyA = (b2PolygonShape*)fA->GetShape();
		b2PolygonShape* polyB = (b2PolygonShape*)fB->GetShape();

		//fill 'subject polygon' from fixtureA polygon
		for (int i = 0; i < polyA->GetVertexCount(); i++)
			outputVertices.push_back( fA->GetBody()->GetWorldPoint( polyA->GetVertex(i) ) );

		//fill 'clip polygon' from fixtureB polygon
		std::vector<b2Vec2> clipPolygon;
		for (int i = 0; i < polyB->GetVertexCount(); i++)
			clipPolygon.push_back( fB->GetBody()->GetWorldPoint( polyB->GetVertex(i) ) );

		b2Vec2 cp1 = clipPolygon[clipPolygon.size()-1];
		for (int j = 0; j < clipPolygon.size(); j++) {
			b2Vec2 cp2 = clipPolygon[j];
			if ( outputVertices.empty() )
				return false;
			std::vector<b2Vec2> inputList = outputVertices;
			outputVertices.clear();
			b2Vec2 s = inputList[inputList.size() - 1]; //last on the input list
			for (int i = 0; i < inputList.size(); i++) {
				b2Vec2 e = inputList[i];
				if (inside(cp1, cp2, e)) {
					if (!inside(cp1, cp2, s)) {
						outputVertices.push_back( intersection(cp1, cp2, s, e) );
					}
					outputVertices.push_back(e);
				}
				else if (inside(cp1, cp2, s)) {
					outputVertices.push_back( intersection(cp1, cp2, s, e) );
				}
				s = e;
			}
			cp1 = cp2;
		}

		return !outputVertices.empty();
	}