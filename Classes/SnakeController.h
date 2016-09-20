#ifndef __SNAKE_CONTROLLER_H__
#define __SNAKE_CONTROLLER_H__
#include "cocos2d.h"

struct IControlSnake
{
	virtual void onAngleChanged(int angle){}
	virtual void onSpeedUp(bool enable){}
	virtual void onSpeedUpOver(){}
	virtual void onGrow(){}
	virtual void onGodLike(){}
};

class SnakeController
{
public:
	static SnakeController *controller();
	void changeAngle(int angle);
	void speedUp(bool enable);
	void speedUpOver();
	void growBody();
	void godLike();

	void addView(IControlSnake *view);
	void removeView(IControlSnake *view);
private:
	std::vector<IControlSnake *>m_views;
};
#endif
