#ifndef __FOOD_MGR_H__
#define __FOOD_MGR_H__
#include "cocos2d.h"
class GamePanel;
class Food;
class FoodMgr
{
public:
	FoodMgr(GamePanel *gamePanel) : m_gamePanel(gamePanel){}
	void update(float dt);
	void snakeToFood();
	void addFood(Food *food);
private:
	void checkKill();
	void genNewFood();
private:
	GamePanel *m_gamePanel;
	std::vector<Food *>m_foods;
};
#endif