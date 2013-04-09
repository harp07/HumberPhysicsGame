#include "GameObject.h"

GameObject::GameObject(const char *imageName, float x, float y, float scale){

	image = imageName;
	scaleX = scaleY = scale;
	posX = x;
	posY = y;

}

void GameObject::spriteInit(cocos2d::CCLayer *layer){

	objSprite = cocos2d::CCSprite::create((image+".png").c_str());
	objSprite->setScaleX(scaleX);
	objSprite->setScaleY(scaleY);
	objSprite->setPosition(ccp(posX, posY));
	layer->addChild(objSprite);

}

void GameObject::physicsInit(b2World *world, shapeType sType, bodyType bType, char* pList){

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
		objBody = world->CreateBody(&objBodyDef);
		objBody->CreateFixture(&objShapeDef);
		break;
	
	case SHAPE_CIRCLE:

		objCircle.m_radius = 
			(scaleX * (objSprite->getContentSize().width/2))/PTM_RATIO;
		objShapeDef.shape = &objCircle;
		objBody = world->CreateBody(&objBodyDef);
		objBody->CreateFixture(&objShapeDef);
		break;
		
	case SHAPE_PLIST:
		GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile(pList);
	
		objBodyDef.position.Set(objSprite->getPositionX()/PTM_RATIO,objSprite->getPositionY()/PTM_RATIO);
		objBody = world->CreateBody(&objBodyDef);

		GB2ShapeCache *_shapeCache = GB2ShapeCache::sharedGB2ShapeCache();
		_shapeCache->addFixturesToBody(objBody,image.c_str());
		objSprite->setAnchorPoint(_shapeCache->anchorPointForShape(image.c_str()));
		break;
	
	}//end switch

}

//void GameObject::updateSprite(b2World *world){
//	
//	if(objBody->GetUserData() != NULL){
//
//		cocos2d::CCSprite *spriteData = (cocos2d::CCSprite *)objBody->GetUserData();
//		spriteData->setPosition(ccp(objBody->GetPosition().x * PTM_RATIO,
//                                    objBody->GetPosition().y * PTM_RATIO));
//		spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(objBody->GetAngle()));
//
//	}
//	
//}