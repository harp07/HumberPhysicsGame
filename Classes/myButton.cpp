#include "..\testp\proj.win32\myButton.h"

//float x y sx sy = A Rectangle.  It's a selection of a graphic within the sprite sheet.
//file is the filename of the sprite sheet.  Buttons are assumed to have 2 different graphics just to be pretty.  
//Layer is there to act as a reference to the Scene itself.
//SEL_MenuHandler accepts a menu_selector(void function)
myButton::myButton(float x, float y, float sx, float sy, const char* file, CCLayer * layer, SEL_MenuHandler sec)
{
	sprite1 = CCSprite::spriteWithFile(file, CCRectMake(x, y, sx, sy));
	sprite2 = CCSprite::spriteWithFile(file, CCRectMake(x + sx, y, sx, sy));
	item1 = CCMenuItemSprite::itemWithNormalSprite(sprite1, sprite2, layer, sec);
	menu = CCMenu::menuWithItems(item1, NULL);
	layer->addChild(menu);
	menu->setPosition(100, 100);
}


myButton::~myButton(void)
{
}

//Relocate
void myButton::SetPosition(float x, float y)
{
	this->xPos = x;
	this->yPos = y;
	menu->setPosition(xPos, yPos);
}