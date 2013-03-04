/*
** GameObject
**
** This class is meant to be an easy alternative to
** the alternative methode, which is to use a huge block
** of code. You will be able to Create a Game Object in 3 lines of code
** and be able to easily set different object properties.
**
** Wladyslaw Bronowicki
** Kiwi Spy Games
*/


#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

#define PTM_RATIO 32.0

class GameObject{

private:

	float posX, posY;
	float scaleX, scaleY;
	b2CircleShape objCircle;
	b2PolygonShape objBox;

	const char *image;

public:

	b2Body *objBody;
	cocos2d::CCSprite *objSprite;
	b2BodyDef objBodyDef;
	
	b2FixtureDef objShapeDef;
	
	/*
	** Enums are used to differentiate what box2d method or property to use
	*/

	enum shapeType {SHAPE_NULL = 0, SHAPE_BOX, SHAPE_CIRCLE};
	enum bodyType {BODY_NULL = 0, BODY_STATIC, BODY_KINIMATIC, BODY_DYNAMIC};

	/*
	** Default Constructor for GameObject
	** Constructors: 
	** Image Name: The file name of the image of the sprite
	** float x and y: The position of the object
	** float scale: the scale of the object
	*/

	GameObject(const char *imageName, float x, float y, float scale);

	/*
	** sprite init is used when creating a sprite
	** CCLayer *layer is the layer you want the sprite to appear on
	*/

	void spriteInit(cocos2d::CCLayer *layer);
	
	/*
	** physicsInit is used to initialize the physics portion of a game object
	** b2World *world is the physics world you wish your object to be placed in
	** bType defines the objects b2DodyDef if it's static, dynamic, or kinematic
	** sType defines the shape to either be a squar or a circle (more will come 
	** as we need them)
	*/

	void physicsInit(b2World *world, shapeType sType, bodyType bType);

	void updateSprite(b2World *world);

	/*
	** Position encapsulation:
	** setObjPos sets the object's position
	** float x and float y require you to give a world position
	**
	**getObjPosX and getObjPosY return the X and Y of the object
	*/



	void setObjPos(float x, float y){
		posX = x;
		posY = y;
	}

	float getObjPosX(){
		return posX;
	}

	float getObjPosY(){
		return posY;
	}

	/*
	** Scale Encapsulation
	** setObjScale scales the object up or down
	** parameters x and y are the scale values
	**
	** getObjScaleX and getObjScaleY return the X and Y scale 
	** values of the object
	*/

	void setObjScale(float x, float y){

		scaleX = x;
		scaleY = y;

	}

	float getObjScaleX(){
		return scaleX;
	}

	float getObjScaleY(){
		return scaleY;
	}

};

#endif