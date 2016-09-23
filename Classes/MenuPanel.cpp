#include "MenuPanel.h"
#include "CommonMacro.h"
#include "UiLayout.h"
#include "MainScene.h"
#include "PackageDialog.h"
#include "SettingDialog.h"
#include "SoundMgr.h"
#include "AndroidIter.h"
using namespace std;
USING_NS_CC;

bool MenuPanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);
	auto bk = CCLayerColor::create(ccc4(175, 175, 175, 255));
	addChild(bk);
	m_layout = UiLayout::create("layout/menu_panel.xml");
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	m_layout->setMenuTouchPriority(kTouchPriorityPanel);
	addChild(m_layout);

	CCMenuItem *newGameBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(1));
	newGameBtn->setTarget(this, menu_selector(MenuPanel::onNewGameBtnClicked));
	CCMenuItem *ruleBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(2));
	ruleBtn->setTarget(this, menu_selector(MenuPanel::onRuleBtnClicked));
	CCMenuItem *skinBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(3));
	skinBtn->setTarget(this, menu_selector(MenuPanel::onSkinBtnClicked));
	CCMenuItem *settingBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(4));
	settingBtn->setTarget(this, menu_selector(MenuPanel::onSettingBtnClicked));

	skinBtn->setVisible(false);
	
	MainScene::theScene()->showDialog(PackageDialog::create());
	
	//auto userId = AndroidIter::getIter()->getUserId();
	CCLabelTTF *idLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(6));
	idLabel->setColor(ccc3(0, 0, 0));
	//idLabel->setString(userId.c_str());
	idLabel->setVisible(false);

	CCLabelTTF *phoneLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	phoneLabel->setColor(ccc3(0, 0, 0));
	phoneLabel->setVisible(false);
    return true;
}

void MenuPanel::onNewGameBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdGamePanel);
}

void MenuPanel::onRuleBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showPanel(kPanelIdHelpPanel);
}

void MenuPanel::onSkinBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
}

void MenuPanel::onSettingBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MainScene::theScene()->showDialog(SettingDialog::create());
}

void MenuPanel::onBackKeyTouched()
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	KeyPadWatcher::exitGame();
}
