#include "GameObject.h"

GameObject::GameObject(const char *imageName, float x, float y, float scale){

	image = imageName;
	scaleX = scaleY = scale;
	posX = x;
	posY = y;

}

void GameObject::spriteInit(cocos2d::CCLayer *layer){

	objSprite = cocos2d::CCSprite::create(image);
	objSprite->setScaleX(scaleX);
	objSprite->setScaleY(scaleY);
	objSprite->setPosition(ccp(posX, posY));
	layer->addChild(objSprite);

}

void GameObject::physicsInit(b2World *world, shapeType sType, bodyType bType){

	objBodyDef.userData = objSprite;

	switch(bType){//begin switch

	case BODY_NULL:
		break;
	
	case BODY_STATIC:
		objBodyDef.type = b2_staticBody;
		break;
	
	case BODY_KINIMATIC:
		objBodyDef.type = b2_kinematicBody;
		break;
	
	case BODY_DYNAMIC:
		objBodyDef.type = b2_dynamicBody;
		break;
	}//end switch

	objBodyDef.position.Set(posX/PTM_RATIO, posY/PTM_RATIO);
	objBodyDef.userData = objSprite;

	switch(sType){//begin switch

	case SHAPE_NULL:
		break;
	
	case SHAPE_BOX:
		objBox.SetAsBox(
			(scaleX * (objSprite->getContentSize().width/2))/PTM_RATIO, 
			(scaleY * (objSprite->getContentSize().height/2))/PTM_RATIO);
		objShapeDef.shape = &objBox;
		break;
	
	case SHAPE_CIRCLE:

		objCircle.m_radius = 
			(scaleX * (objSprite->getContentSize().width/2))/PTM_RATIO;
		objShapeDef.shape = &objCircle;
		break;
	}//end switch

	
	objBody = world->CreateBody(&objBodyDef);
	objBody->CreateFixture(&objShapeDef);

}

void GameObject::updateSprite(b2World *world){
	
	if(objBody->GetUserData() != NULL){

		cocos2d::CCSprite *spriteData = (cocos2d::CCSprite *)objBody->GetUserData();
		spriteData->setPosition(ccp(objBody->GetPosition().x * PTM_RATIO,
                                    objBody->GetPosition().y * PTM_RATIO));
		spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(objBody->GetAngle()));

	}
	
}