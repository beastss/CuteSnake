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

void TestScene::testBatchNode()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("snake/aaa.plist");
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("snake/aaa.png");
	CCSprite* sprite1 = CCSprite::createWithSpriteFrameName("精灵帧1的名字");
	CCSprite* sprite2 = CCSprite::createWithSpriteFrameName("精灵帧2的名字");
	batchNode->addChild(sprite1);
	batchNode->addChild(sprite2);
	addChild(batchNode);
}
