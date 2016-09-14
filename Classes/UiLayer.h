#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "cocos2d.h"

class UiLayer : public cocos2d::CCNode
{
public:
	CREATE_FUNC(UiLayer);
private:
    virtual bool init();  
    void menuCloseCallback(cocos2d::CCObject* pSender);
	void onJoyStickChanged(int angle);
};

#endif 
