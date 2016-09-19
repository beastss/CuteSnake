#ifndef __FOOD_H__
#define __FOOD_H__
#include "cocos2d.h"

class Food :
	public cocos2d::CCNode
{
public:
	static Food *create(cocos2d::CCPoint pos, cocos2d::ccColor3B color);
	void onEaten(cocos2d::CCPoint pt);
private:
	Food(cocos2d::CCPoint pos, cocos2d::ccColor3B color): m_pos(pos), m_color(color){}
private:
	virtual bool init();
private:
	cocos2d::CCPoint m_pos;
	cocos2d::ccColor3B m_color;
};
#endif