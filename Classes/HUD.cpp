#include "HUD.h"


HUD * HUD::m_singleton;

HUD * HUD::getInstance()
{
	if (!m_singleton)
		m_singleton = new HUD();
	
	return m_singleton;
}

void HUD::addButton(Button * button)
{
	button->button()->setZOrder(4);
	menu->addChild(button->button());
}

void HUD::addBar(Bar * bar)
{
	bar->bar()->setZOrder(4);
	menu->addChild(bar->bar());
}

void HUD::addLabel(Label * label)
{
	label->_label()->setZOrder(4);
	menu->addChild(label->_label());
}


HUD::HUD(void)
{
	menu = CCMenu::create();
	menu->setZOrder(4);
}


HUD::~HUD(void)
{

}

CCMenu * HUD::GetHUD()
{
	//menu->alignItemsVertically();
	return menu;
}
