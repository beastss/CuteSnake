#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class GameLayer : public cocos2d::CCNode
{
public:
	CREATE_FUNC(GameLayer);
private:
    virtual bool init();  
    void menuCloseCallback(cocos2d::CCObject* pSender);
};

#endif 
