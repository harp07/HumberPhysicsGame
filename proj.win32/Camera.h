#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

using namespace cocos2d;

class Camera {
private:
	Camera();
	static Camera* m_singleton;
	CCLayer* mainLayer;
public:
	static Camera* cameraInstance();
	void moveCamera(CCPoint location);
	void setFocus(CCPoint location);
	void reset();
	void setLayer(CCLayer* layer);
};

#endif