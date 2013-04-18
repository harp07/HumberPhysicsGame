#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "b2DebugDraw.h"
#include "BouyancyContactListener.h"
#include "Globals.h"
#include "GameObject.h"
#include "Ship.h"
#include "HUD.h"
#include "Projectile.h"

using namespace cocos2d;


class GameWorld
{
private:
	GameWorld();
	static GameWorld* m_singleton;
	b2World* m_world;
	b2DebugDraw *m_DebugDraw;
	CCLayer* mainLayer;
	CCSize screenSize;
	bool debugDrawBool;
	bool projectileFired;
	float shots;
	bool moving;
public:
	static GameWorld* worldInstance();
	void setLayer(CCLayer* layer);
	b2World* getWorld();
	void createWorld();
	void draw();
	void setBackground(const char* _location);
	void updateWorld(float dt);
	void shoot();
	void debugVisuals();
	void addArt();
	void moveShip();
	b2Body* getPlayer();
	void addObjects();
	BouyancyContactListener myListener;
	b2Vec2 _waterPos;
	b2Vec2 _waterSize;
	GameObject* projectile;
	CCSprite* waterAlphaSprite;
	CCSprite* waterSprite;
	CCSprite* backgroundSprite;
	CCSprite* hudBottom;
	CCSprite* hudTop;

	//Buttons
	Button * left, * right, * fire;
	Button * xpowup, * xpowdown, 
		   * ypowup, * ypowdown, 
		   * angleup, * angledown;
	
	//Labels
	Label * xPowstr, * yPowstr, * angleStr, * playerName, * enemyName;

	//bars
	Bar * playerhp, * enemyhp;

	void leftbutton(CCObject * sender);
	void rightbutton(CCObject * sender);
	void firebutton(CCObject * sender);
	void XPOWUP(CCObject * sender);
	void XPOWDOWN(CCObject * sender);
	void YPOWUP(CCObject * sender);
	void YPOWDOWN(CCObject * sender);
	void ANGLEUP(CCObject * sender);
	void ANGLEDOWN(CCObject * sender);


	float currentpowerx;
	float currentpowery;

	float currentangle;

	void createHUD();

	Ship* player;
	Ship* enemy;
	Projectile* proj;
};

#endif  // __GAME_WORLD__