#include "GameLayer.h"
#include "PlayerSnake.h"
using namespace std;
USING_NS_CC;

bool GameLayer::init()
{
	auto bk = CCLayerColor::create(ccc4(120, 120, 120, 255));
	addChild(bk);
	
	auto playerSnake = PlayerSnake::create();
	playerSnake->setPosition(ccp(200, 200));
	addChild(playerSnake);
    return true;
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCMessageBox("test", "test");
}
