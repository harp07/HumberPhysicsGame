#include "Bar.h"


Bar::Bar(const char * file, CCLayer * target, float anchorx, float anchory)
{
	item = CCMenuItemImage::create(file, file, target, NULL);
	item->setAnchorPoint(CCPoint(anchorx, anchory));
	scalex = item->getScaleX();
	scaley = item->getScaleY();
	x = item->getPositionX();
	y = item->getPositionY();
}


Bar::~Bar()
{

}

void Bar::SetPosition(float x, float y)
{
	item->setPosition(x, y);
}

void Bar::SetScale(float x, float y)
{
	item->setScaleX(x);
	item->setScaleY(y);
}

float Bar::GetScaleX()
{
	return scalex;
}

float Bar::GetScaleY()
{
	return scaley;
}

float Bar::GetX()
{
	return x;
}

float Bar::GetY()
{
	return y;
}

CCMenuItemImage * Bar::bar()
{
	return item;
}