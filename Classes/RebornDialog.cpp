#include "RebornDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "GamePanel.h"
#include "PlayerSnake.h"
#include "GameOverDialog.h"
#include "PlayerData.h"
#include "MyPurchase.h"
#include "SoundMgr.h"
USING_NS_CC;
using namespace std;

RebornDialog *RebornDialog::create(GamePanel *gamePanel)
{
	RebornDialog *dialog = new RebornDialog(gamePanel);
	dialog->init();
	dialog->autorelease();
	return dialog;
}

bool RebornDialog::init()
{
	m_layout = UiLayout::create("layout/reborn.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	
	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	closeBtn->setTarget(this, menu_selector(RebornDialog::onCloseBtnClicked));

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(RebornDialog::onBuyBtnClicked));

	return true;
}

void RebornDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MyPurchase::sharedPurchase()->buyItem(kBillingReborn, [=]()
	{
		//复活后回复上次长度
		auto snake = PlayerSnake::create(m_gamePanel, PlayerData::theData()->getData());
		m_gamePanel->addSnake(snake);
		removeFromParent();
	});
}

void RebornDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(GameOverDialog::create());
	removeFromParent();
}