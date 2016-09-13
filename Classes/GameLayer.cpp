#include "GameLayer.h"
using namespace std;
USING_NS_CC;

bool GameLayer::init()
{
	auto bk = CCLayerColor::create(ccc4(120, 120, 120, 255));
	addChild(bk);

    return true;
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCMessageBox("test", "test");
}
