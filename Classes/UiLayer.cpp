#include "UiLayer.h"
#include "CommonUtil.h"
#include "JoyStick.h"
#include "SnakeController.h"
#include "CommonMacro.h"
#include "UiLayout.h"
#include "..\CoolSatrs\Classes\EmptyBox.h"
#include "RankingPanel.h"
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
	m_layout = UiLayout::create("layout/game_panel_ui.xml");
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	m_layout->setMenuTouchPriority(kTouchPriorityPanel);
	addChild(m_layout);

	CCMenuItem *speedUpBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(1));
	speedUpBtn->setTarget(this, menu_selector(UiLayer::onSpeedUpBtnClicked));
	CCMenuItem *growBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(2));
	growBtn->setTarget(this, menu_selector(UiLayer::onGrowBtnClicked));
	CCMenuItem *godLikeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(3));
	godLikeBtn->setTarget(this, menu_selector(UiLayer::onGodLikeBtnClicked));
	
	EmptyBox *box = dynamic_cast<EmptyBox *>(m_layout->getChildById(8));
	box->setNode(RankingPanel::create());

	//ÐéÄâÒ¡¸Ë
	auto joyStick = JoyStick::create();
	joyStick->setHandle(bind(&UiLayer::onJoyStickChanged, this, placeholders::_1));
	addChild(joyStick);

    return true;
}

void UiLayer::onSpeedUpBtnClicked(CCObject* pSender)
{
	SnakeController::controller()->speedUp();
	CCMenuItem *speedUpBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(1));
	speedUpBtn->setEnabled(false);
}

void UiLayer::onGodLikeBtnClicked(CCObject* pSender)
{
	SnakeController::controller()->godLike();
}

void UiLayer::onGrowBtnClicked(CCObject* pSender)
{
	SnakeController::controller()->growBody();
}

void UiLayer::onJoyStickChanged(int angle)
{
	//CCLOG("x = %f, y = %f", angel.x, angel.y);
	SnakeController::controller()->changeAngle(angle);
}

void UiLayer::onSpeedUpOver()
{
	CCMenuItem *speedUpBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(1));
	speedUpBtn->setEnabled(true);
}

