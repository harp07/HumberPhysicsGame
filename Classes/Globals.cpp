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

void Globals::Output(float szFormat){
	std::wostringstream _os;
	_os << szFormat << "\n";
	//OutputDebugStringW(_os.str().c_str());
	/*char szBuff[1024];
	va_list arg;
	va_start(arg,szFormat);
	_vsnprintf(szBuff, sizeof(szBuff),szFormat,arg);
	OutputDebugStringW((LPCWSTR)szBuff);*/
}

void Globals::setLayer(CCLayer* layer){
	mainLayer = layer;
}

CCLayer* Globals::getLayer(){
	return mainLayer;
}

void Globals::setWorld(b2World* world){
	m_world = world;
}

b2World* Globals::getWorld(){
	return m_world;
}

void Globals::setWaterheight(float height){
	waterHeight = height;
}

float Globals::getWaterheight(){
	return waterHeight;
}

void Globals::setPlayerHealth(float health){
	playerHealth = health;
}

float Globals::getPlayerHealth(){
	return playerHealth;
}

void Globals::setEnemyHealth(float health){
	enemyHealth = health;
}

float Globals::getEnemyHealth(){
	return enemyHealth;
}

void Globals::setUnitTurn(bool turn){
	unitTurn = turn;
}
bool Globals::getUnitTurn(){
	return unitTurn;
}
