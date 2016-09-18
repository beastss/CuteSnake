#include "TestScene.h"
#include "GameConfig.h"
#include "PlayerSnake.h"
using namespace std;
USING_NS_CC;

bool TestScene::init()
{
	if (!CCScene::init())return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	auto bk = CCLayerColor::create(ccc4(120, 120, 120, 255));
	addChild(bk);
	//int value = GameConfigSelf->getIntValue("plist", "sjdf2");

	//auto snake = PlayerSnake::create();
	//addChild(snake);
	//snake->setPosition(ccp(100, 100));

	auto spr = CCSprite::create("ui/speed_up.png");
	addChild(spr);
	spr->setPosition(ccp(100, 100));
	spr->setRotation(-45);
    return true;
}

