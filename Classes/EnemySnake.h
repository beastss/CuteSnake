#ifndef __ENEMY_SNAKE_H__
#define __ENEMY_SNAKE_H__ 
#include "Snake.h"

class GamePanel;

class EnemySnake : public Snake
{
public:
	static EnemySnake *create(GamePanel *gamePanel);
private:
	EnemySnake(GamePanel *gamePanel);
	virtual bool init();
	virtual void onExit();

	virtual void onMove(cocos2d::CCPoint pos);
	virtual void onDead();
	void detectCollision();
};
#endif