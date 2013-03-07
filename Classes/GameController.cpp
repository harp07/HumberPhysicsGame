#include "GameController.h"


GameController::GameController(void)
{

}


GameController::~GameController(void)
{

}

//For test purposes, this just closes the program.
void GameController::logic(CCObject * pSender)
{
	 CCDirector::sharedDirector()->end();
}