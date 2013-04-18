#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "cocos2d.h"
#include "GameObject.h"

using namespace cocos2d;

class Button
{
public:
	Button(const char * file, CCLayer * target, SEL_MenuHandler evt);
	~Button(void);
	void SetPosition(float x, float y);
	void SetScale(float x, float y);
	float GetScaleX();
	float GetScaleY();
	float GetX();
	float GetY();
	CCMenuItemImage * button();

private:
	CCMenuItemImage * item;
	float x, y;
	float scalex, scaley;	

};

#endif