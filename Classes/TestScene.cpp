#include "TestScene.h"
using namespace std;
USING_NS_CC;

bool TestScene::init()
{
	if (!CCScene::init())return false;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	auto bk = CCLayerColor::create(ccc4(120, 120, 120, 255));
	addChild(bk);
	CCDictionary* pDict = CCDictionary::createWithContentsOfFile("data/plist.xml");
	const CCString* name = pDict->valueForKey("sjdf1");
    return true;
}

