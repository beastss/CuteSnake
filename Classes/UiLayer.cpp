#include "UiLayer.h"
#include "CommonUtil.h"
#include "JoyStick.h"
#include "SnakeController.h"
#include "CommonMacro.h"
#include "UiLayout.h"
#include "EmptyBox.h"
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
	initLeftUi();
	initRightUi();
	//ÐéÄâÒ¡¸Ë
	auto joyStick = JoyStick::create();
	joyStick->setHandle(bind(&UiLayer::onJoyStickChanged, this, placeholders::_1));
	addChild(joyStick);

    return true;
}

void UiLayer::initLeftUi()
{
	m_leftLayout = UiLayout::create("layout/game_panel_ui_left.xml");
	m_leftLayout->setMenuTouchPriority(kTouchPriorityPanel);
	addChild(m_leftLayout);

	CCMenuItem *growBtn = dynamic_cast<CCMenuItem *>(m_leftLayout->getChildById(2));
	growBtn->setTarget(this, menu_selector(UiLayer::onGrowBtnClicked));
	CCMenuItem *godLikeBtn = dynamic_cast<CCMenuItem *>(m_leftLayout->getChildById(3));
	godLikeBtn->setTarget(this, menu_selector(UiLayer::onGodLikeBtnClicked));
	CCLabelTTF *lengthLabel = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(5));
	CCLabelTTF *scoreLabel = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(7));
	for (int i = 0; i < 4; ++i)
	{
		CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(4 + i));
		label->setColor(ccc3(70, 130, 180));
	}
}

void UiLayer::initRightUi()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_rightLayout = UiLayout::create("layout/game_panel_ui_right.xml");
	m_rightLayout->setMenuTouchPriority(kTouchPriorityPanel);
	m_rightLayout->setAnchorPoint(ccp(1, 0));
	m_rightLayout->setPosition(ccp(winSize.width, 0));
	addChild(m_rightLayout);

	CCMenuItem *speedUpBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(1));
	speedUpBtn->setTarget(this, menu_selector(UiLayer::onSpeedUpBtnClicked));
	EmptyBox *box = dynamic_cast<EmptyBox *>(m_rightLayout->getChildById(8));
	box->setNode(RankingPanel::create());
}


void UiLayer::onSpeedUpBtnClicked(CCObject* pSender)
{
	SnakeController::controller()->speedUp();
	CCMenuItem *speedUpBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(1));
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
	CCMenuItem *speedUpBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(1));
	speedUpBtn->setEnabled(true);
}

