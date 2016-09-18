#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BasePanel.h"
class UiLayer;
class Snake;
class GamePanel : public BasePanel
{
public:
	CREATE_FUNC(GamePanel);
	void setFocus(cocos2d::CCPoint pos);
	std::vector<Snake *> getSnakes(){ return m_snakes; }
	void removeSnake(Snake *snake);
private:
    virtual bool init();  
	void initSnakes();
	void addSnake(Snake *snake);
private:
	UiLayer *m_uiLayer;
	cocos2d::CCNode *m_snakeField;
	std::vector<Snake *> m_snakes;
};

#endif 
