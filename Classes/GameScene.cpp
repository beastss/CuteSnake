#include "GameScene.h"
#include "CommonUtil.h"
#include "JoyStick.h"
using namespace std;
USING_NS_CC;

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCMenuItem *btn = CommonUtil::getScaleMenuItemSpr("CloseNormal.png");
	btn->setTarget(this, menu_selector(GameScene::menuCloseCallback));
	btn->setPosition(ccp(100, 200));
	CCMenu* pMenu = CCMenu::create(btn, NULL);
    this->addChild(pMenu, 1);

	auto joyStick = JoyStick::create();
	joyStick->setHandle(bind(&GameScene::onJoyStickChanged, this, placeholders::_1));
	addChild(joyStick);
	
    return true;
}

void GameScene::onJoyStickChanged(CCPoint angel)
{
	CCLOG("x = %f, y = %f", angel.x, angel.y);
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	CCMessageBox("test", "test");
}
