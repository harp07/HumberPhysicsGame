#ifndef _BAR_H_
#define _BAR_H_

#include "cocos2d.h"
#include "GameObject.h"

using namespace cocos2d;

class Bar
{


public:
	Bar(const char * file, CCLayer * target, float anchorx, float anchory);
	~Bar();
	void SetPosition(float x, float y);
	void SetScale(float x, float y);
	float GetScaleX();
	float GetScaleY();
	float GetX();
	float GetY();
	CCMenuItemImage * bar();

private:
	CCMenuItemImage * item;
	float x, y;
	float scalex, scaley;


};


#endif