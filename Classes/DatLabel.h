#ifndef _DAT_LABEL_H_
#define _DAT_LABEL_H_

#include <cocos2d.h>

using namespace cocos2d;

class Label
{
public:

	Label(const char * file, CCLayer * target);
	~Label(void);
	void SetPosition(float x, float y);
	void SetText(const char * string);
	CCLabelTTF * _label();
private:
	CCLabelTTF * label;
};

#endif