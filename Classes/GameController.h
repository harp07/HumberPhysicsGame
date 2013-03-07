#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <cocos2d.h>

using namespace cocos2d;

class GameController
{
public:
	GameController(void);
	~GameController(void);
	void logic(CCObject * pSender);
	//add more void functions as needed
};
	

#endif