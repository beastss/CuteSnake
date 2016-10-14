#ifndef __MY_PURCHASE_H__
#define __MY_PURCHASE_H__

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#endif 
#include <functional>

USING_NS_CC;

enum ReturnCode
{
	kReturnCodeSucceed,
	kReturnCodeFail,
	kReturnCodeCanceled, 
};

enum ToastText
{
	kToastTextNotEnoughDiamond,
	kToastTextNotEnoughFood,
	kToastTextNotEnoughStrength,
};

enum BillingIndex
{
	kBillingReborn,
	kBillingPackage,
	kBillingSkin,
};

struct BillingData
{
	std::string name;
	std::string desc;
	bool canRepeatedBuy;
	int cost;
	std::string code;
};

struct BillingParam
{
	std::function<void()> modelCallback;//model�ص� ��֤������Ч
	int whichUi;//whichUiΪUi�����ַ
	std::function<void()> uiCallback;//ui�ص���������Ч�����removeUiCallback���Ƴ��Լ�

	BillingParam()
	{
		modelCallback = std::function<void()>();
		whichUi = 0;
		uiCallback = std::function<void()>();
	}
};

class ActionRunner;
class MyPurchaseResult
{
public:
	void onPayResult(int ret, const char* msg){}
	void setHandle(){}
};

class MyPurchase
{
public:
	static MyPurchase* sharedPurchase();
	void removeUiCallback(int whichUi);
	void buyItem(int id, const BillingParam &param);

	void onPayResult(int ret);
	void showToast(int index);
	void initBillingData();
	BillingData getBillData(int id){ return m_billingData[id]; }
private:
	MyPurchase();
	~MyPurchase();
	void reset();
	bool checkBuyType(int type);
private:
	bool m_purchasing;
	BillingParam m_billParam;
	ActionRunner *m_runner;	
	std::vector<BillingData> m_billingData;
};
#endif