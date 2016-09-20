#include "GameOverDialog.h"
#include "UILayout.h"
#include "MainScene.h"
USING_NS_CC;
using namespace std;

bool GameOverDialog::init()
{
	m_layout = UiLayout::create("layout/game_over_panel.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	
	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	backBtn->setTarget(this, menu_selector(GameOverDialog::onBackBtnClicked));

	CCMenuItem *replayBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	replayBtn->setTarget(this, menu_selector(GameOverDialog::onReplayBtnClicked));

	CCLabelTTF *label = NULL;
	label = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	label->setColor(ccc3(255, 0, 0));
	label = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(8));
	label->setColor(ccc3(0, 0, 0));
	label = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(9));
	label->setColor(ccc3(255, 0, 0));
	label = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(10));
	label->setColor(ccc3(0, 0, 0));
	return true;
}

void GameOverDialog::onReplayBtnClicked(cocos2d::CCObject* pSender)
{
	MainScene::theScene()->showPanel(kPanelIdGamePanel);
	removeFromParent();
}

void GameOverDialog::onBackBtnClicked(cocos2d::CCObject* pSender)
{
	MainScene::theScene()->showPanel(kPanelIdMenuPanel);
	removeFromParent();
}