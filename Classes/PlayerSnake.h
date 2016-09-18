#ifndef __PLAYER_SNAKE_H__
#define __PLAYER_SNAKE_H__ 
#include "Snake.h"
#include "SnakeController.h"

class ActionRunner;
class PlayerSnake 
	: public Snake
	, public IControlSnake
{
public:
	CREATE_FUNC(PlayerSnake);
	~PlayerSnake();
private:
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
	PlayerSnake();
private:
	virtual void onAngleChanged(int angle);
	virtual void onSpeedUp();
private:
	ActionRunner *m_runner;
	bool m_isSpeedUp;
};
#endif