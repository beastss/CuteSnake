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

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(RebornDialog::onBuyBtnClicked));

	CCLabelTTF *costLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	int cost = MyPurchase::sharedPurchase()->getBillData(kBillingReborn).cost / 100;
	char str[100] = { 0 };
	sprintf(str, costLabel->getString(), cost);
	costLabel->setString(str);

	bool forBusiness = AndroidIter::getIter()->isForBusiness();
	if (forBusiness)
	{
		costLabel->setOpacity(10);
	}

	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(forBusiness ? 5 : 8));
	closeBtn->setTarget(this, menu_selector(RebornDialog::onCloseBtnClicked));
	m_layout->getChildById(5)->setVisible(forBusiness);
	m_layout->getChildById(8)->setVisible(!forBusiness);
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

void RebornDialog::onTouch(cocos2d::CCPoint pt)
{
	bool forBusiness = AndroidIter::getIter()->isForBusiness();
	if (!forBusiness) return;
	MyPurchase::sharedPurchase()->buyItem(kBillingReborn, [=]()
	{
		//复活后回复上次长度
		auto snake = PlayerSnake::create(m_gamePanel, PlayerData::theData()->getData());
		m_gamePanel->addSnake(snake);
		removeFromParent();
	});
}