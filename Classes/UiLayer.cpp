#include "UiLayer.h"
#include "CommonUtil.h"
#include "JoyStick.h"
#include "SnakeController.h"
using namespace std;
USING_NS_CC;

void UiLayer::onEnter()
{
	CCNode::onEnter();
	SnakeController::controller()->addView(this);
}

void UiLayer::onExit()
{
	CCNode::onExit();
	SnakeController::controller()->removeView(this);
}

bool UiLayer::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	//°´Å¥
	m_speedUpBtn = CommonUtil::getScaleMenuItemSpr("ui/speed_up.png");
	m_speedUpBtn->setTarget(this, menu_selector(UiLayer::menuCloseCallback));
	m_speedUpBtn->setPosition(ccp(winSize.width * 0.4f, winSize.height * -0.3f));
	CCMenu* pMenu = CCMenu::create(m_speedUpBtn, NULL);
	this->addChild(pMenu, 1);

	//ĞéÄâÒ¡¸Ë
	auto joyStick = JoyStick::create();
	joyStick->setHandle(bind(&UiLayer::onJoyStickChanged, this, placeholders::_1));
	addChild(joyStick);

    return true;
}

void UiLayer::menuCloseCallback(CCObject* pSender)
{
	SnakeController::controller()->speedUp();
	m_speedUpBtn->setEnabled(false);
}

void UiLayer::onJoyStickChanged(int angle)
{
	//CCLOG("x = %f, y = %f", angel.x, angel.y);
	SnakeController::controller()->changeAngle(angle);
}

void UiLayer::onSpeedUpOver()
{
	m_speedUpBtn->setEnabled(true);
}

