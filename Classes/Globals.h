#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

#define PTM_RATIO 32.0

using namespace cocos2d;
class Globals {
private:
	Globals();
	static Globals* m_Globals;
public:
	static Globals* globalsInstance();
	CCSize screenSize();
	void Output(float szFormat);
};

#endif