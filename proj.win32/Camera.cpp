#include "Camera.h"

using namespace cocos2d;

Camera* Camera::m_singleton = NULL;

Camera::Camera(){

}

Camera* Camera::cameraInstance(){
	if(NULL == m_singleton){
		m_singleton = new Camera();
	}
	return m_singleton;
}

void Camera::setLayer(CCLayer* layer){
	mainLayer = layer;
}

void Camera::moveCamera(CCPoint location){
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	if(location.x < (screenSize.width/2)/32.0){
		mainLayer->setPosition(mainLayer->getPosition().x-location.x,mainLayer->getPosition().y+location.y);
	} else if (location.x > (screenSize.width/2)/32.0){
		mainLayer->setPosition(mainLayer->getPosition().x+location.x,mainLayer->getPosition().y-location.y);
	}
}

void Camera::setFocus(CCPoint location){
	mainLayer->setScale(1.5f);
	mainLayer->setAnchorPoint(location);
}

void Camera::reset(){
	mainLayer->setScale(1.0f);
}