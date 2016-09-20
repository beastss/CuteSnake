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
	auto data = MyPurchase::sharedPurchase()->getBillData();
	for (size_t i = 0; i < data.size(); ++i)
	{
		auto label = CCLabelTTF::create(data[i].name.c_str(), "Arial", 20);
		label->setPosition(ccp(100, 100 + 30 * i));
		addChild(label);
	}
    return true;
}

