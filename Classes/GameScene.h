#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameScene);
private:
    virtual bool init();  
    void menuCloseCallback(cocos2d::CCObject* pSender);
	void onJoyStickChanged(cocos2d::CCPoint angel);
};

#endif 
