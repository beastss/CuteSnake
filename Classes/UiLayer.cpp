#include "UiLayer.h"
#include "CommonUtil.h"
#include "JoyStick.h"
#include "SnakeController.h"
using namespace std;
USING_NS_CC;

bool UiLayer::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	//°´Å¥
	CCMenuItem *btn = CommonUtil::getScaleMenuItemSpr("ui/speed_up.png");
	btn->setTarget(this, menu_selector(UiLayer::menuCloseCallback));
	btn->setPosition(ccp(winSize.width * 0.4f, winSize.height * -0.3f));
	CCMenu* pMenu = CCMenu::create(btn, NULL);
	this->addChild(pMenu, 1);

	//ÐéÄâÒ¡¸Ë
	auto joyStick = JoyStick::create();
	joyStick->setHandle(bind(&UiLayer::onJoyStickChanged, this, placeholders::_1));
	addChild(joyStick);

    return true;
}

void UiLayer::menuCloseCallback(CCObject* pSender)
{
	CCMessageBox("test", "test");
}

void UiLayer::onJoyStickChanged(int angle)
{
	//CCLOG("x = %f, y = %f", angel.x, angel.y);
	SnakeController::controller()->changeAngle(angle);
}
