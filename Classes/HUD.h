#ifndef _HEADS_UP_DISPLAY_H_
#define _HEADS_UP_DISPLAY_H_

#include "cocos2d.h"
#include "DatButton.h"
#include "Bar.h"
#include "DatLabel.h"


using namespace cocos2d;

class HUD
{
public:
	static HUD * getInstance();
	~HUD(void);
	void addButton(Button * button);
	void addBar(Bar * bar);
	void addLabel(Label * label);
	CCMenu * GetHUD();

private:
	CCMenu * menu;
	HUD(void);
	static HUD * m_singleton;
};

#endif