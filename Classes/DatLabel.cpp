#include "DatLabel.h"


Label::Label(const char * file, CCLayer * target)
{
	label = CCLabelTTF::create(file,"Arial",20);

}


Label::~Label(void)
{

}

void Label::SetPosition(float x, float y)
{
	label->setPosition(CCPoint(x, y));
}

void Label::SetText(const char * string)
{
	label->setString(string);
}

CCLabelTTF * Label::_label()
{
	return label;
}
