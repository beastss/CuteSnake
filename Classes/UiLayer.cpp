#include "UiLayer.h"
#include "CommonUtil.h"
#include "JoyStick.h"
#include "SnakeController.h"
#include "CommonMacro.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "RankingPanel.h"
#include "PropsMgr.h"
#include "MainScene.h"
#include "PackageDialog.h"
#include "PlayerData.h"
#include "SoundMgr.h"
using namespace std;
USING_NS_CC;

void UiLayer::onEnter()
{
	CCNode::onEnter();
	SnakeController::controller()->addView(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kTouchPriorityPanel, true);
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
	CCLabelAtlas *growNum = dynamic_cast<CCLabelAtlas *>(m_leftLayout->getChildById(8));
	growNum->setString(CommonUtil::intToStr(PropsMgr::theMgr()->getNum(kPropsTypeGrow)));
	CCMenuItem *godLikeBtn = dynamic_cast<CCMenuItem *>(m_leftLayout->getChildById(3));
	CCLabelAtlas *godLikeNum = dynamic_cast<CCLabelAtlas *>(m_leftLayout->getChildById(9));
	godLikeNum->setString(CommonUtil::intToStr(PropsMgr::theMgr()->getNum(kPropsTypeGodlike)));;
	godLikeBtn->setTarget(this, menu_selector(UiLayer::onGodLikeBtnClicked));
	for (int i = 0; i < 4; ++i)
	{
		CCLabelTTF *label = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(4 + i));
		label->setColor(ccc3(70, 130, 180));
	}
	onSnakeDataChanged();
}

void UiLayer::initRightUi()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_rightLayout = UiLayout::create("layout/game_panel_ui_right.xml");
	m_rightLayout->setMenuTouchPriority(kTouchPriorityPanel);
	m_rightLayout->setAnchorPoint(ccp(1, 0));
	m_rightLayout->setPosition(ccp(winSize.width, 0));
	addChild(m_rightLayout);

	auto rankingPanel = RankingPanel::create();
	rankingPanel->setAnchorPoint(ccp(1, 1));
	rankingPanel->setPosition(ccpSub(winSize, ccp(5, 5)));
	rankingPanel->setScale(0.7f);
	addChild(rankingPanel);

	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>(m_rightLayout->getChildById(10));
	backBtn->setTarget(this, menu_selector(UiLayer::onBackBtnClicked));
#if(CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	backBtn->setVisible(false);
#endif
}

void UiLayer::onGodLikeBtnClicked(CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	int num = PropsMgr::theMgr()->getNum(kPropsTypeGodlike);
	if (num <= 0)
	{
		//MainScene::theScene()->showDialog(PackageDialog::create());
		return;
	}
	PropsMgr::theMgr()->saveNum(kPropsTypeGodlike, num - 1);
	CCLabelAtlas *growNum = dynamic_cast<CCLabelAtlas *>(m_leftLayout->getChildById(9));
	growNum->setString(CommonUtil::intToStr(num - 1));

	SnakeController::controller()->godLike();
}

void UiLayer::onGrowBtnClicked(CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	int num = PropsMgr::theMgr()->getNum(kPropsTypeGrow);
	if (num <= 0)
	{
		//MainScene::theScene()->showDialog(PackageDialog::create());
		return;
	}
	PropsMgr::theMgr()->saveNum(kPropsTypeGrow, num - 1);
	CCLabelAtlas *growNum = dynamic_cast<CCLabelAtlas *>(m_leftLayout->getChildById(8));
	growNum->setString(CommonUtil::intToStr(num - 1));

	SnakeController::controller()->growBody();
}

void UiLayer::onBackBtnClicked(CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
}

void UiLayer::onJoyStickChanged(int angle)
{
	//CCLOG("x = %f, y = %f", angel.x, angel.y);
	SnakeController::controller()->changeAngle(angle);
}

void UiLayer::onSnakeDataChanged()
{
	int length = PlayerData::theData()->getData().length;
	int score = PlayerData::theData()->getData().score;
	CCLabelTTF *lengthLabel = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(5));
	lengthLabel->setString(CommonUtil::intToStr(length));
	CCLabelTTF *scoreLabel = dynamic_cast<CCLabelTTF *>(m_leftLayout->getChildById(7));
	scoreLabel->setString(CommonUtil::intToStr(score));
}

bool UiLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto pos = m_rightLayout->convertToNodeSpace(pTouch->getLocation());
	auto speedUpImg = m_rightLayout->getChildById(1);
	if (speedUpImg->boundingBox().containsPoint(pos))
	{
		SoundMgr::theMgr()->playEffect(kEffectMusicButton);
		speedUpImg->setScale(1.3f);
		SnakeController::controller()->speedUp(true);
		return true;
	}
	return false;
}

void UiLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_rightLayout->getChildById(1)->setScale(1);
	SnakeController::controller()->speedUp(false);
}
