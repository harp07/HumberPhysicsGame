#include "DatButton.h"


Button::Button(const char * file, CCLayer * target, SEL_MenuHandler evt)
{
	item = CCMenuItemImage::create(file, file, target, evt);
	scalex = item->getScaleX();
	scaley = item->getScaleY();
	x = item->getPositionX();
	y = item->getPositionY();
}


Button::~Button(void)
{
}

void Button::SetPosition(float x, float y)
{
	item->setPosition(x, y);
}

void Button::SetScale(float x, float y)
{
	item->setScaleX(x);
	item->setScaleY(y);
}

float Button::GetScaleX()
{
	return scalex;
}

float Button::GetScaleY()
{
	return scaley;
}

float Button::GetX()
{
	return x;
}

float Button::GetY()
{
	return y;
}

CCMenuItemImage * Button::button()
{
	return item;
}