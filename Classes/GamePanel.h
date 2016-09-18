#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BasePanel.h"
class UiLayer;
class GamePanel : public BasePanel
{
public:
	CREATE_FUNC(GamePanel);
	void setFocus(cocos2d::CCPoint pos);
	void initSnakes();
private:
    virtual bool init();  
private:
	UiLayer *m_uiLayer;
	cocos2d::CCNode *m_snakeField;
};

#endif 
