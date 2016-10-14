#include "RebornDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "GamePanel.h"
#include "PlayerSnake.h"
#include "GameOverDialog.h"
#include "PlayerData.h"
#include "MyPurchase.h"
#include "SoundMgr.h"
#include "AndroidIter.h"
USING_NS_CC;
using namespace std;

void RebornDialog::onEnter()
{
	ScaleDialog::onEnter();
}

void RebornDialog::onExit()
{
	ScaleDialog::onExit();
	MyPurchase::sharedPurchase()->removeUiCallback((int)this);
}

RebornDialog *RebornDialog::create(GamePanel *gamePanel)
{
	RebornDialog *dialog = new RebornDialog(gamePanel);
	dialog->init();
	dialog->autorelease();
	return dialog;
}

bool RebornDialog::init()
{
	bool forBusiness = AndroidIter::getIter()->isForBusiness();

	m_layout = UiLayout::create(forBusiness ? "layout/reborn.xml" : "layout/reborn_white.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(RebornDialog::onBuyBtnClicked));

	CCLabelTTF *costLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	CCLabelTTF *phoneLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(9));
	int cost = MyPurchase::sharedPurchase()->getBillData(kBillingReborn).cost / 100;
	char str[100] = { 0 };
	sprintf(str, costLabel->getString(), cost);
	costLabel->setString(str);
	phoneLabel->setColor(ccc3(0, 0, 0));
	phoneLabel->setVisible(false);
	if (forBusiness)
	{
		costLabel->setOpacity(10);
		

		//phoneLabel->setOpacity(10);
	}
	else
	{
		costLabel->setColor(ccc3(0, 0, 0));
	}

	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	closeBtn->setTarget(this, menu_selector(RebornDialog::onCloseBtnClicked));
	return true;
}

void RebornDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	doBiling();
}

void RebornDialog::doBiling()
{
	BillingParam param;
	param.whichUi = (int)this;
	param.uiCallback = [=]()
	{
		//复活后回复上次长度
		auto snake = PlayerSnake::create(m_gamePanel, PlayerData::theData()->getData());
		m_gamePanel->addSnake(snake);
		removeFromParent();
	};

	MyPurchase::sharedPurchase()->buyItem(kBillingReborn, param);
}

void RebornDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(GameOverDialog::create());
	removeFromParent();
}

void RebornDialog::onTouch(cocos2d::CCPoint pt)
{
	bool forBusiness = AndroidIter::getIter()->isForBusiness();
	if (!forBusiness) return;

	doBiling();
}