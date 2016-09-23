#include "PackageDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "MyPurchase.h"
#include "PropsMgr.h"
#include "SoundMgr.h"
#include "AndroidIter.h"
USING_NS_CC;
using namespace std;

bool PackageDialog::init()
{
	m_layout = UiLayout::create("layout/package.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);


	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(PackageDialog::onBuyBtnClicked));

	CCLabelTTF *costLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	int cost = MyPurchase::sharedPurchase()->getBillData(kBillingPackage).cost / 100;
	char str[100] = { 0 };
	sprintf(str, costLabel->getString(), cost);
	costLabel->setString(str);

	bool forBusiness = AndroidIter::getIter()->isForBusiness();
	if (forBusiness)
	{
		costLabel->setOpacity(10);
	}

	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(forBusiness ? 5 : 8));
	closeBtn->setTarget(this, menu_selector(PackageDialog::onCloseBtnClicked));
	m_layout->getChildById(5)->setVisible(forBusiness);
	m_layout->getChildById(8)->setVisible(!forBusiness);
	return true;
}

void PackageDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	MyPurchase::sharedPurchase()->buyItem(kBillingPackage, [=]()
	{
		int num = PropsMgr::theMgr()->getNum(kPropsTypeGrow);
		PropsMgr::theMgr()->saveNum(kPropsTypeGrow, num + 10);

		num = PropsMgr::theMgr()->getNum(kPropsTypeGodlike);
		PropsMgr::theMgr()->saveNum(kPropsTypeGodlike, num + 10);

		removeFromParent();
	});
}

void PackageDialog::onCloseBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	removeFromParent();
}

void PackageDialog::onTouch(cocos2d::CCPoint pt)
{
	bool forBusiness = AndroidIter::getIter()->isForBusiness();
	if (!forBusiness) return;
	MyPurchase::sharedPurchase()->buyItem(kBillingPackage, [=]()
	{
		int num = PropsMgr::theMgr()->getNum(kPropsTypeGrow);
		PropsMgr::theMgr()->saveNum(kPropsTypeGrow, num + 10);

		num = PropsMgr::theMgr()->getNum(kPropsTypeGodlike);
		PropsMgr::theMgr()->saveNum(kPropsTypeGodlike, num + 10);
	});
}