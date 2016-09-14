#ifndef __PLAYER_SNAKE_H__
#define __PLAYER_SNAKE_H__ 
#include "Snake.h"
#include "SnakeController.h"

class PlayerSnake 
	: public Snake
	, public IControlSnake
{
public:
	CREATE_FUNC(PlayerSnake);
private:
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
private:
	virtual void onAngleChanged(int angle);
	virtual void onSpeedUp();

};
#endif