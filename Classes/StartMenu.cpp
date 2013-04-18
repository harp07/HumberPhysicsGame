#include "StartMenu.h"

using namespace cocos2d;

CCScene* StartMenu::scene(){

	CCScene * scene = NULL;
    
	do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StartMenu *layer = StartMenu::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);

    } while (0);

    // return the scene
    return scene;

}

bool StartMenu::init(){

	bool bRet = false;
	do
	{

		//////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		        // Create a "close" menu igtem with close icon, it's an auto release object.
        CCMenuItemImage *menu_Start = CCMenuItemImage::create(
            "start.png",
            "start.png",
            this,
			menu_selector(StartMenu::menuStartCall));
        CC_BREAK_IF(! menu_Start);
		menu_Start->setScaleX(winSize.width/menu_Start->getContentSize().width/2);
		menu_Start->setScaleY(winSize.height/menu_Start->getContentSize().height/8);


        CCMenuItemImage *menu_Instruct = CCMenuItemImage::create("instructions.png",
            "instructions.png",
            this,
            NULL);
        CC_BREAK_IF(! menu_Instruct);

		menu_Instruct->setPosition(ccp(X_OFFSET, menu_Start->getPosition().y - menu_Instruct->getContentSize().height) );
		menu_Instruct->setScaleX(winSize.width/menu_Instruct->getContentSize().width/2);
		menu_Instruct->setScaleY(winSize.height/menu_Instruct->getContentSize().height/8);

		CCMenuItemImage *menu_Options = CCMenuItemImage::create("options.png",
            "options.png",
            this,
            NULL);
        CC_BREAK_IF(! menu_Options);

		menu_Options->setPosition(ccp(X_OFFSET, menu_Instruct->getPosition().y - menu_Options->getContentSize().height));
		menu_Options->setScaleX(winSize.width/menu_Options->getContentSize().width/2);
		menu_Options->setScaleY(winSize.height/menu_Options->getContentSize().height/8);

		CCMenuItemImage *menu_Credits = CCMenuItemImage::create("credits.png",
            "credits.png",
            this,
            NULL);
        CC_BREAK_IF(! menu_Credits);

		menu_Credits->setPosition(ccp(X_OFFSET, menu_Options->getPosition().y - menu_Credits->getContentSize().height));
		menu_Credits->setScaleX(winSize.width/menu_Credits->getContentSize().width/2);
		menu_Credits->setScaleY(winSize.height/menu_Credits->getContentSize().height/8);	

		CCMenu* menu = CCMenu::create(menu_Start, menu_Options, menu_Instruct, menu_Credits, NULL);
		//menu->setScale(0.9);
		menu->setPosition(ccp(winSize.width/2, winSize.height/1.30));
        CC_BREAK_IF(! menu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(menu, 1);

		bRet = true;
	}while(0);

	return bRet;
}

void StartMenu::menuStartCall(CCObject* pSender){

	CCDirector::sharedDirector()->replaceScene(GameScene::scene());

}