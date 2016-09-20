#ifndef __FOOD_H__
#define __FOOD_H__
#include "cocos2d.h"

class Food :
	public cocos2d::CCNode
{
public:
	static Food *create(cocos2d::ccColor3B color, bool isSnakeBody = false);
	int getEnergy(){ return m_enery; }
	void onEaten(cocos2d::CCPoint pt);
private:
	Food(cocos2d::ccColor3B color, bool isSnakeBody) : m_color(color), m_isSnakeBody(isSnakeBody){}
private:
	virtual bool init();
private:
	bool m_isSnakeBody;
	cocos2d::ccColor3B m_color;
	int m_enery;
};
#endif