#include "PackageDialog.h"
#include "UILayout.h"
#include "MainScene.h"
#include "MyPurchase.h"
#include "PropsMgr.h"
#include "SoundMgr.h"
#include "AndroidIter.h"
USING_NS_CC;
using namespace std;

void PackageDialog::onEnter()
{
	ScaleDialog::onEnter();
}

void PackageDialog::onExit()
{
	ScaleDialog::onExit();
	MyPurchase::sharedPurchase()->removeUiCallback((int)this);
}

bool PackageDialog::init()
{
	bool forBusiness = AndroidIter::getIter()->isForBusiness();

	m_layout = UiLayout::create(forBusiness ? "layout/package.xml" : "layout/package_white.xml");
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);


	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(6));
	buyBtn->setTarget(this, menu_selector(PackageDialog::onBuyBtnClicked));

	CCLabelTTF *costLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(7));
	CCLabelTTF *phoneLabel = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(9));
	int cost = MyPurchase::sharedPurchase()->getBillData(kBillingPackage).cost / 100;
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
		costLabel->setColor(ccc3(0, 0, 0));;
	}

	CCMenuItem *closeBtn = dynamic_cast<CCMenuItem *>(m_layout->getChildById(5));
	closeBtn->setTarget(this, menu_selector(PackageDialog::onCloseBtnClicked));
	return true;
}

void PackageDialog::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	SoundMgr::theMgr()->playEffect(kEffectMusicButton);
	doBilling();
}

void PackageDialog::doBilling(bool removeUi)
{
	BillingParam param;
	param.modelCallback = bind(&PropsMgr::buyPropsPackage, PropsMgr::theMgr());
	param.whichUi = (int)this;
	if (removeUi)
	{
		param.uiCallback = [=]()
		{
			removeFromParent();
		};
	}
	
	MyPurchase::sharedPurchase()->buyItem(kBillingPackage, param);
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

	doBilling(false);
}