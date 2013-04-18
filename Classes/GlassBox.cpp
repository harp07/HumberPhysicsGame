#include "GlassBox.h"
#include "GameWorld.h"
#include "Globals.h"

GlassBox* GlassBox::singleGlassBox = NULL;

GlassBox::GlassBox()
{
	currentState = 0;
	maxDistanceFromPlayer = 10;
	speed = 50;
	nextStep = 0;
}

void GlassBox::update(float dt)
{
	Globals::globalsInstance()->Output(9090.0f);

	float distanceFromPlayer = 0;
	
	if(tempEnemy != NULL && tempPlayer != NULL)
	distanceFromPlayer = tempEnemy->GetWorldCenter().x - tempPlayer->GetWorldCenter().x;


	switch(currentState)
	{
	case GlassBox::State::IDLE :
		//Stand still and slow down AI ship

		//Slow Down AI ship
		tempEnemy->SetLinearVelocity(b2Vec2(tempEnemy->GetLinearVelocity().x * 0.2f, tempEnemy->GetLinearVelocity().y));
		currentState = State::DEFENDING;
		if(!Globals::globalsInstance()->getUnitTurn())
			currentState = GlassBox::State::ATTACKING;
		break;
	case State::ATTACKING :
		//Move around and attack player
		if(distanceFromPlayer >= maxDistanceFromPlayer * 0.5f)
		{
			tempEnemy->ApplyForce(b2Vec2(speed, 0), tempEnemy->GetWorldCenter());
			currentState = State::IDLE;
			GameWorld::worldInstance()->shootAI();
		} else
		{
			tempEnemy->ApplyForce(b2Vec2(-speed, 0), tempEnemy->GetWorldCenter());
			currentState = State::DEFENDING;
		}
		break;
	case State::DEFENDING :
		//Move away from player and attack player
		
		if(distanceFromPlayer >= maxDistanceFromPlayer)
		{
			tempEnemy->ApplyForce(b2Vec2(-speed, 0), tempEnemy->GetWorldCenter());
			//if enemy health > 50%
			currentState = State::ATTACKING;
		}

		if(!Globals::globalsInstance()->getUnitTurn())
			currentState = State::ATTACKING;
		break;
	}
}

GlassBox* GlassBox::getGlassBox()
{
	if(singleGlassBox == NULL)
	{
		singleGlassBox = new GlassBox();
	}
	return singleGlassBox;
}

void GlassBox::setAIOnBody(b2Body *playerBody,b2Body *aiBody)
{

	tempPlayer = playerBody;
	tempEnemy = aiBody;

	//Globals::globalsInstance()->getLayer()->scheduleOnce(schedule_selector(GlassBox::update), 1/60);
	if(nextStep >= 75)
	{
		Globals::globalsInstance()->Output(8080.0f);
		GlassBox::update(1);
		nextStep = 0;
	}
	nextStep++;
}