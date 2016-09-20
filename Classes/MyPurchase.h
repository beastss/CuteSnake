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
	kBillingPackage,
	kBillingSkin,
	kBillingReborn,
};

struct BillingData
{
	std::string name;
	std::string desc;
	bool canRepeatedBuy;
	int cost;
	std::string code;
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
	void buyItem(int id, std::function<void()> callback);

	static void onPayResult(int ret);
	void showToast(int index);
	void initBillingData();
	std::vector<BillingData> getBillData(){ return m_billingData; }
private:
	MyPurchase();
	~MyPurchase();
	bool checkBuyType(int type);
private:
	static std::function<void()> s_callback;
	static ActionRunner *s_runner;	
	std::vector<BillingData> m_billingData;
};
#endif