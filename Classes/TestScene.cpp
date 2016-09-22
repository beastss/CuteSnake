#include "TestScene.h"
#include "GameConfig.h"
#include "PlayerSnake.h"
#include "MyPurchase.h"
using namespace std;
USING_NS_CC;

bool TestScene::init()
{
	if (!CCScene::init())return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	auto bk = CCLayerColor::create(ccc4(120, 120, 120, 255));
	addChild(bk);

	MyPurchase::sharedPurchase()->initBillingData();

    return true;
}

