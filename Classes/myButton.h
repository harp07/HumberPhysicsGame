#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "../testp/proj.win32/GameController.h"

using namespace cocos2d;

class myButton
{
	public:
		myButton(float x, float y, float sx, float sy, const char * file, CCLayer * layer, SEL_MenuHandler sec);
		~myButton(void);
		void SetPosition(float x, float y);
		float xPos, yPos;

	private:
		CCSprite * sprite1;
		CCSprite * sprite2;
		CCMenu * menu;
		CCMenuItemSprite * item1; 
		
};
