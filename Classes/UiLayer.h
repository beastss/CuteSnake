#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"
#include "SnakeController.h"

class UiLayer
	: public cocos2d::CCNode
	, public IControlSnake
{
public:
	CREATE_FUNC(UiLayer);
private:
    virtual bool init();  
    void menuCloseCallback(cocos2d::CCObject* pSender);
	void onJoyStickChanged(int angle);
	virtual void onEnter();
	virtual void onExit();
private:
	virtual void onSpeedUpOver();
private:
	cocos2d::CCMenuItem *m_speedUpBtn;
};

#endif 
