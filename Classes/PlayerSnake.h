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
	static PlayerSnake *create(GamePanel *gamePanel);
	~PlayerSnake();
private:
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
	PlayerSnake(GamePanel *gamePanel);
	virtual void onDead();
	virtual void onMove(cocos2d::CCPoint pos);
private:
	virtual void onAngleChanged(int angle);
	virtual void onSpeedUp();
private:
	ActionRunner *m_runner;
	bool m_isSpeedUp;
};
#endif