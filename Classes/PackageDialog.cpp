#include "PackageDialog.h"
#include "UILayout.h"
#include "MainScene.h"
USING_NS_CC;
using namespace std;

bool PackageDialog::init()
{
	m_layout = UiLayout::create("layout/package.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	
	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	closeBtn->setTarget(this, menu_selector(PackageDialog::onCloseBtnClicked));

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(PackageDialog::onBuyBtnClicked));

	return true;
}

void PackageDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	removeFromParent();
}

void PackageDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	removeFromParent();
}