#include "Globals.h"

using namespace cocos2d;

Globals* Globals::m_Globals = NULL;

Globals::Globals() {}
	
Globals* Globals::globalsInstance(){
	if(NULL == m_Globals){
		m_Globals = new Globals();
	}
	return m_Globals;
}
	
CCSize Globals::screenSize(){
	return CCDirector::sharedDirector()->getWinSize();
}