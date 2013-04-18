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
	float touchLocation = location.x - currentTouchLocation.x;
	//Globals::globalsInstance()->Output(touchLocation);
	if(touchLocation < 0){
		mainLayer->setPosition(mainLayer->getPosition().x-(location.x/(PTM_RATIO/3)),0.0f);
	} else if (touchLocation > 0){
		mainLayer->setPosition(mainLayer->getPosition().x+(location.x/(PTM_RATIO/3)),0.0f);
	} 
	setLocation(location);
}

void Camera::setFocus(CCPoint location){

	mainLayer->setScale(1.5f);
	mainLayer->setAnchorPoint(location);
	//Globals::globalsInstance()->Output(location.x);
	//Globals::globalsInstance()->Output(location.y);
	
}

void Camera::reset(){
	mainLayer->setScale(1.0f);
}

void Camera::setLocation(CCPoint location){
	currentTouchLocation = location;
}