#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class GameLayer;
class UiLayer;
class MainScene : public cocos2d::CCScene
{
public:
	CREATE_FUNC(MainScene);
private:
    virtual bool init();  
private:
	GameLayer *m_gameLayer;
	UiLayer *m_uiLayer;

};

#endif 
