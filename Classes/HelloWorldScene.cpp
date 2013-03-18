#include "HelloWorldScene.h"
#include "particle.h"

#define PTM_RATIO 32.0

using namespace cocos2d;



void HelloWorld::update(float dt)
{

	int32 velocityIterations = 10;
	int32 positionIterations = 10;
	m_world->Step(dt,velocityIterations,positionIterations);

	p->update(dt);
	//p->wind = p->wind + 1;

		if(f){
			if(i < 10){
				ball = CCSprite::create("ball.png");
		 //CC_BREAK_IF(! ball);

				 ball->setScale(0.5f);

				 addChild(ball,0);
				//b2BodyDef sphereDef;
				sphereDef.type = b2_dynamicBody;
				sphereDef.userData = ball;
				sphereDef.position.Set(x/PTM_RATIO,y/PTM_RATIO);//  /PTM_RATIO
				_sphere[i] = m_world->CreateBody(&sphereDef);
				b2CircleShape sphereShape;

				sphereShape.m_radius = 10.0f /PTM_RATIO;
				b2FixtureDef sphereFix;
				sphereFix.shape = &sphereShape;
				sphereFix.restitution = 1.0f;
				sphereFix.density = 20.0f;
				_sphere[i]->CreateFixture(&sphereFix);
  
				//_sphere[i]->ApplyAngularImpulse(10.0f);
				//_sphere[i]->ApplyLinearImpulse(b2Vec2(5.0f,5.0f),b2Vec2(0.0f,0.0f));
				i++;
			}
			f = false;
		//}else{
			//j++;
		}
		if(i > 0){
			vector = b2Vec2(_sphere[i-1]->GetPosition().x - _box->GetPosition().x, _sphere[i-1]->GetPosition().y - _box->GetPosition().y);
			//vector = b2Vec2(_sphere[i-1]->GetLocalVector().x - _box->GetLocalVector().x, _sphere[i-1]->GetLocalVector().y - _box->GetLocalVector().y);
			desiredAngle = atan2f(vector.y,vector.x);
			nextAngle = _box->GetAngle() + _box->GetAngularVelocity() * (1.0/60.0);
			totalRotation = desiredAngle - nextAngle;
			desiredAngularVelocity = totalRotation / (1.0/60.0);
			_box->ApplyAngularImpulse(_box->GetInertia() * desiredAngularVelocity);
		}
		//_sphere[i]->GetPosition().//,_box->GetPosition);
		
		

		 

		/*for(b2Body *b = m_world->GetBodyList(); b != NULL; b = b->GetNext()) 
   {    
      if (b->GetUserData() != NULL) {
           CCSprite *sprite = (CCSprite *) b->GetUserData();
		   sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
           sprite->setRotation(CC_RADIANS_TO_DEGREES(b->GetAngle() * -1));
       }       
   }*/

		//_sphere[i]->SetUserData(ball);
		//ball->setPosition(_sphere[i]->GetPosition);
m_world->ClearForces();
}
CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
	{
        CC_BREAK_IF(! CCLayer::init());

		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		p = new particle(this);
		
		gravity = b2Vec2(0.0f,-9.8f);
		m_world = new b2World(gravity);
		m_world->SetContinuousPhysics(true);
		//setTouchEnabled(true);
		//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); 
		//CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


		/*b2Body *_sphere[10];
  for(int i = 0; i < 10; i ++){
   b2BodyDef sphereDef;
   sphereDef.type = b2_dynamicBody;
   sphereDef.position.Set((90.0f + (i*2))/PTM_RATIO,200.0f/PTM_RATIO);
   _sphere[i] = m_world->CreateBody(&sphereDef);
   b2CircleShape sphereShape;

   sphereShape.m_radius = 10.0f /PTM_RATIO;
   b2FixtureDef sphereFix;
   sphereFix.shape = &sphereShape;
   sphereFix.restitution = 1.0f;
   sphereFix.density = 20.0f;
   _sphere[i]->CreateFixture(&sphereFix);
  }*/

		//b2Body *_sphere[10];
			i = 0;
			j = 0;
			f = false;

   
	    	/*b2Body *_box;
	     b2BodyDef boxDef;*/

		 this->setTouchEnabled(true);
		 this->setKeypadEnabled(true);

		 //schedule(schedule_selector(HelloWorld::update),1/60);
		 scheduleUpdate();
		 boxDef.type = b2_dynamicBody;
		 boxDef.userData = box;
		 //_sphere[i]->SetUserData(ball);
		 boxDef.position.Set(350.0f / PTM_RATIO,300.0f / PTM_RATIO);
		 boxDef.gravityScale = 0.0f;
		 _box       = m_world->CreateBody(&boxDef);
		 b2PolygonShape boxShape;

		 boxShape.SetAsBox(20  / PTM_RATIO, 10 / PTM_RATIO);
		 b2FixtureDef boxFix;
		 boxFix.shape = &boxShape;
		 boxFix.density = 10.0f;
		 boxFix.restitution = 1.0f;
		 _box->CreateFixture(&boxFix);

		 //ball = CCSprite::create("ball.png");
		 //CC_BREAK_IF(! ball);

		 //ball->setScale(0.5f);
		 ////ball->setPosition(ccp(50,50));
		 //addChild(ball,0);

		 box = CCSprite::create("wooden_box.jpg");
		 CC_BREAK_IF(! box);

		 box->setScale(0.1f);
		 addChild(box,0);


		// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(screenSize.width/2/PTM_RATIO, screenSize.height/2/PTM_RATIO); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;
    // bottom
    groundBox.SetAsBox(screenSize.width/2/PTM_RATIO, 0, b2Vec2(0, -screenSize.height/2/PTM_RATIO), 0);
 	groundBody->CreateFixture(&groundBox, 0);
	
    // top
    groundBox.SetAsBox(screenSize.width/2/PTM_RATIO, 0, b2Vec2(0, screenSize.height/2/PTM_RATIO), 0);
    groundBody->CreateFixture(&groundBox, 0);

    // left
    groundBox.SetAsBox(0, screenSize.height/2/PTM_RATIO, b2Vec2(-screenSize.width/2/PTM_RATIO, 0), 0);
    groundBody->CreateFixture(&groundBox, 0);

    // right
    groundBox.SetAsBox(0, screenSize.height/2/PTM_RATIO, b2Vec2(screenSize.width/2/PTM_RATIO, 0), 0);
    groundBody->CreateFixture(&groundBox, 0);

		///////////////////////////////////////////////////////////////////////////////////
		//For Box2d Debug Drawing//
		m_DebugDraw = new b2DebugDraw(PTM_RATIO);
		m_world->SetDebugDraw(m_DebugDraw);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		m_DebugDraw->SetFlags(flags);





		//////////////////////////////////////////////////////////////////////////////////

		//m_emitter = new CCParticleSystemQuad();



		//// Gravity Mode
		//this->m_nEmitterMode = kCCParticleModeGravity;
		//// Gravity Mode: gravity

		//this->modeA.gravity = ccp(0,-90);

        bRet = true;
    } while (0);

    return bRet;
}
void HelloWorld::draw(void)
{

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    m_world->DrawDebugData();

    kmGLPopMatrix();

    
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocation();
		//CCParticleSystemQuad* m_emitter = new CCParticleSystemQuad();
    	//m_emitter = CCParticleFire::create();
		//m_emitter->addChild(ball);
		//m_emitter->setPosition(location.x,location.y);
		//smoke(location);
		if(location.x > 200){
			p->fire(location);
		}else{
			p->smoke(location);
		}
		//p->rain(0.0f,100.0f,300.0f);
		x = location.x;
		y = location.y;
		f = true;
        //addNewSpriteAtPosition( location );
    }

}
void HelloWorld::Keyboard(unsigned char key)
  {
  switch (key)
    {
      case 'w': //up       
		  float vx;
		float vy;
        break;
      default:
        //run default behaviour
        HelloWorld::Keyboard(key);
    ;}
  }
void HelloWorld::smoke(CCPoint location){

 m_emitter = CCParticleSmoke::create();
 m_emitter->retain();
 m_emitter->setPosition(location);

 ccColor4F startColor = {0.1f, 0.1f, 0.1f, 1.0f};
     m_emitter->setStartColor(startColor);

     //ccColor4F startColorVar = {0.5f, 0.f, 0.5f, 1.0f};
     //m_emitter->setStartColorVar(startColorVar);

     ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
     m_emitter->setEndColor(endColor);

     ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
     m_emitter->setEndColorVar(endColorVar);

     m_emitter->setScale(0.5f);
     m_emitter->setGravity(ccp(0.0f,-200.0f));
     m_emitter->setLife(2.0f);
     m_emitter->setTotalParticles(10);
     m_emitter->setDuration(1.0f);

 this->addChild(m_emitter, 1);

 m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fireball2.png"));

 m_emitter->setAutoRemoveOnFinish(true);
}



