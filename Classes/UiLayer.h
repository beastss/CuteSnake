#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"
#include "SnakeController.h"

class UiLayout;
class UiLayer
	: public cocos2d::CCNode
	, public IControlSnake
{
public:
	CREATE_FUNC(UiLayer);
private:
    virtual bool init();  
	void initLeftUi();
	void initRightUi();
	void onSpeedUpBtnClicked(cocos2d::CCObject* pSender);
	void onGodLikeBtnClicked(cocos2d::CCObject* pSender);
	void onGrowBtnClicked(cocos2d::CCObject* pSender);
	void onJoyStickChanged(int angle);
	virtual void onEnter();
	virtual void onExit();
private:
	virtual void onSpeedUpOver();
private:
	UiLayout *m_leftLayout;
	UiLayout *m_rightLayout;
};

#endif 
