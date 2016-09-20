#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BasePanel.h"
class UiLayer;
class Snake;
class Food;
class FoodMgr;

class GamePanel : public BasePanel
{
public:
	CREATE_FUNC(GamePanel);
	void setFocus(cocos2d::CCPoint pos);
	std::vector<Snake *> getSnakes(){ return m_snakes; }
	void removeSnake(Snake *snake);
	void addFood(Food *food);
	void addSnake(Snake *snake);
	~GamePanel();
private:
	GamePanel();
    virtual bool init();  
	void initGameBk();
	void initSnakes();
	void update(float dt);
private:
	UiLayer *m_uiLayer;
	cocos2d::CCNode *m_snakeField;
	FoodMgr *m_foodMgr;
	std::vector<Snake *> m_snakes;
};

#endif 
