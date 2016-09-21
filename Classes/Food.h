#ifndef __FOOD_H__
#define __FOOD_H__
#include "cocos2d.h"

class Food 
{
public:
	Food(cocos2d::ccColor3B color, bool isSnakeBody);
	~Food();
	int getEnergy(){ return m_enery; }
	void onEaten(cocos2d::CCPoint pt);
	cocos2d::CCSprite *getView(){ return m_view; }
private:
	void init();
private:
	bool m_isSnakeBody;
	cocos2d::ccColor3B m_color;
	int m_enery;
	cocos2d::CCSprite *m_view;
};
#endif