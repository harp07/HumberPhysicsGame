#include "BouyancyContactListener.h"


BouyancyContactListener::BouyancyContactListener()
{
	
}

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

		/*if(contact->GetFixtureA()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_SHIP && contact->GetFixtureB()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_WATER){
			Globals::globalsInstance()->Output(1);
		} 

		if(contact->GetFixtureA()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_WATER && contact->GetFixtureB()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_SHIP){
			Globals::globalsInstance()->Output(2);
		}

		if(contact->GetFixtureA()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_WATER && contact->GetFixtureB()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_GROUND){
			Globals::globalsInstance()->Output(3);
		} 

		if(contact->GetFixtureA()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_GROUND && contact->GetFixtureB()->GetBody()->GetUserData() == (void*)Globals::globalsInstance()->BODY_WATER){
			Globals::globalsInstance()->Output(4);
		}
		*/

		void* bodyUserData = contact->GetFixtureA()->GetUserData();
      if ( bodyUserData )
		  static_cast<Projectile*>( bodyUserData )->startContact(contact->GetFixtureB()->GetBody()->GetPosition());
  
      //check if fixture B was a ball
      /*bodyUserData = contact->GetFixtureB()->GetUserData();

      if ( bodyUserData )
		  static_cast<Projectile*>( bodyUserData )->startContact(contact->GetFixtureB()->GetBody()->GetPosition());*/
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

		//check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
          static_cast<Projectile*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
          static_cast<Projectile*>( bodyUserData )->endContact();

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

void BouyancyContactListener::update(float dt){
	std::set<fixturePair>::iterator it = m_fixturePairs.begin();
    std::set<fixturePair>::iterator end = m_fixturePairs.end();
    while (it != end) {

        //fixtureA is the fluid
        b2Fixture* fixtureA = it->first;
        b2Fixture* fixtureB = it->second;

        float density = fixtureA->GetDensity();

        std::vector<b2Vec2> intersectionPoints;
        if (findIntersectionOfFixtures(fixtureA, fixtureB, intersectionPoints) ) {

            //find centroid
            float area = 0;
            b2Vec2 centroid = ComputeCentroid( intersectionPoints, area);

            //apply buoyancy force
            float displacedMass = fixtureA->GetDensity() * area;
            b2Vec2 gravity( 0, -10 );
            b2Vec2 buoyancyForce = displacedMass * -gravity;
            fixtureB->GetBody()->ApplyForce( buoyancyForce, centroid);

            /*
            //simple drag
            //find relative velocity between object and fluid
            b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( centroid ) -
                    fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( centroid );
            float vel = velDir.Normalize();

            float dragMod = 1;//adjust as desired
            float dragMag = fixtureA->GetDensity() * vel * vel;
            b2Vec2 dragForce = dragMod * dragMag * -velDir;
            fixtureB->GetBody()->ApplyForce( dragForce, centroid,true );
            float angularDrag = area * -fixtureB->GetBody()->GetAngularVelocity();
            fixtureB->GetBody()->ApplyTorque( angularDrag );
            */

            //apply complex drag
            float dragMod = 0.25f;//adjust as desired
            float liftMod = 0.25f;//adjust as desired
            float maxDrag = 2000;//adjust as desired
            float maxLift = 500;//adjust as desired
            for (int i = 0; i < intersectionPoints.size(); i++) {
                b2Vec2 v0 = intersectionPoints[i];
                b2Vec2 v1 = intersectionPoints[(i+1)%intersectionPoints.size()];
                b2Vec2 midPoint = 0.5f * (v0+v1);

                //find relative velocity between object and fluid at edge midpoint
                b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( midPoint ) -
                        fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( midPoint );
                float vel = velDir.Normalize();

                b2Vec2 edge = v1 - v0;
                float edgeLength = edge.Normalize();
                b2Vec2 normal = b2Cross(-1,edge);
                float dragDot = b2Dot(normal, velDir);
                if ( dragDot < 0 )
                    continue;//normal points backwards - this is not a leading edge

                //apply drag
                float dragMag = dragDot * dragMod * edgeLength * density * vel * vel;
                dragMag = b2Min( dragMag, maxDrag );
                b2Vec2 dragForce = dragMag * -velDir;
                fixtureB->GetBody()->ApplyForce( dragForce, midPoint);

                //apply lift
                float liftDot = b2Dot(edge, velDir);
                float liftMag =  dragDot * liftDot * liftMod * edgeLength * density * vel * vel;
                liftMag = b2Min( liftMag, maxLift );
                b2Vec2 liftDir = b2Cross(1,velDir);
                b2Vec2 liftForce = liftMag * liftDir;
                fixtureB->GetBody()->ApplyForce( liftForce, midPoint );
            }

            //draw debug info
        /*    glColor3f(0,1,1);
            glLineWidth(2);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < intersectionPoints.size(); i++)
                glVertex2f( intersectionPoints[i].x, intersectionPoints[i].y );
            glEnd();
            glLineWidth(1);*/
                
            //line showing buoyancy force
            /*if ( area > 0 ) {
                glBegin(GL_LINES);
                glVertex2f( centroid.x, centroid.y );
                glVertex2f( centroid.x, centroid.y + area );
                glEnd();
            }*/
        }

        ++it;
    }
}

void BouyancyContactListener::CreateWater(b2Vec2 pos,b2Vec2 size, float density,float friction)
{
	//if(getWorld() == NULL){
	waterDef.type = b2_staticBody;
  waterDef.position.Set(pos.x / PTM_RATIO,pos.y/ PTM_RATIO);
  waterDef.angle = 0.0f;
  
  waterDef.linearVelocity.Set(0.0f, 0.0f);
  waterDef.angularVelocity = 0.0;
  waterDef.linearDamping = 0.0f;
  waterDef.angularDamping = 0.0f;
  waterDef.allowSleep = true;
  waterDef.awake = false;
  waterDef.fixedRotation = false;
  waterDef.bullet = false;
  waterDef.active =true ;
  waterDef.gravityScale = 1.0f;
  _water = m_world->CreateBody(&waterDef);

  
    b2FixtureDef waterFix;
  
    waterFix.restitution = 0.0f;
    
    waterFix.isSensor =  bool(1);
    waterFix.filter.categoryBits = uint16(2);
    waterFix.filter.maskBits = uint16(65535);
    waterFix.filter.groupIndex = int16(0);
	waterFix.density = density;
	waterFix.friction = friction;
    b2PolygonShape waterShape;
    

	waterShape.SetAsBox(size.x,size.y,b2Vec2(0.0f,0.0f),0.0f);

    waterFix.shape = &waterShape;

    _water->CreateFixture(&waterFix);
	//_water->SetUserData((void*)Globals::globalsInstance()->BODY_WATER);
}

void BouyancyContactListener::setWorld(b2World* world){
	m_world = world;
}

b2World* BouyancyContactListener::getWorld(){
	return 0;
}