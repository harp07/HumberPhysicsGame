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
	OutputDebugStringW(_os.str().c_str());
	/*char szBuff[1024];
	va_list arg;
	va_start(arg,szFormat);
	_vsnprintf(szBuff, sizeof(szBuff),szFormat,arg);
	OutputDebugStringW((LPCWSTR)szBuff);*/
}